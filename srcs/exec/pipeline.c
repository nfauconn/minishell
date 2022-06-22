/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:32:33 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/22 12:49:30 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int8_t	exit_code = 0;

static void	exec_cmd(t_sh *sh, t_cmd *cmd)
{
	if (!cmd->name)
		exit(0);
	cmd->env = get_env_tab(sh->env);
	if (cmd->name && access(cmd->name, X_OK) != -1)
		execve(cmd->name, cmd->args, cmd->env);
	cmd->env_paths = get_path_tab(sh->env);
	if (!cmd->env_paths || !find_path(cmd, cmd->env_paths))
		exit_code = NOT_FOUND;
	else
	{	
		execve(cmd->path, cmd->args, cmd->env);
		exit_code = NOT_EXECUTABLE;
	}
	error_exit(cmd->name, exit_code);
}

void	child_seq(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	close(p[0]);
	if (cmd->redir_in == REDIR_FAIL || cmd->redir_out == REDIR_FAIL)
		exit(WRONG_REDIR);
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

	cmd = sh->cmd_list;
	fd_in = 0;
	signal_catching_mode(PGM_EXEC);
	while (cmd)
	{
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
	return (sh->last_exit_code);
}
