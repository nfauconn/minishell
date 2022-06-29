/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:32:33 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/29 21:46:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_sh *sh, t_cmd *cmd)
{
	if (!cmd->name)
		exit(0);
	cmd->env = get_env_tab(sh->env);
	if (cmd->name && access(cmd->name, X_OK) != -1)
		execve(cmd->name, cmd->args, cmd->env);
	cmd->env_paths = get_path_tab(sh->env);
	if (!cmd->env_paths || !find_path(cmd, cmd->env_paths))
		error_exit(cmd->name, NOT_FOUND);
	else
	{	
		execve(cmd->path, cmd->args, cmd->env);
		error_exit(cmd->name, NOT_EXECUTABLE);
	}
	error_exit(cmd->name, 1);
}

void	child_seq(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	signal_catching_mode(CHILD);
	close(p[0]);
	if (cmd->redir_in == REDIR_FAIL || cmd->redir_out == REDIR_FAIL)
	{
		close(p[1]);
		exit(WRONG_REDIR);
	}
	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	else if (fd_in)
		dup2_close_old(fd_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(p[1], STDOUT_FILENO);
	close(p[1]);
	exec_cmd(sh, cmd);
}

void	parent_seq(int p[2], int *fd)
{
	close(p[1]);
	close_if_exists(*fd);
	*fd = p[0];
}

int	cmd_execute(t_sh *sh)
{
	int		p[2];
	int		fd_in;
	pid_t	pid;
	t_cmd	*cmd;
	int		i;

	cmd = sh->cmd_list;
	fd_in = 0;
	signal_catching_mode(PGM_EXEC);
	while (cmd)
	{
		i = is_builtin(cmd->name);
		if (i >= 0)
		{
			sh->exec_built[i](sh, cmd);
			cmd = cmd->next;
			continue ;
		}
		if (pipe(p) < 0)
			return (exec_error("pipe: ", strerror(errno)));
		pid = fork();
		if (pid < 0)
			return (exec_error("fork: ", strerror(errno)));
		if (pid == 0)
			child_seq(sh, cmd, p, fd_in);
		else
			parent_seq(p, &fd_in);
		cmd = cmd->next;
	}
	wait_children(sh);
	signal_catching_mode(INTERACTIVE);
	return (sh->last_status);
}
