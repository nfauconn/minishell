/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:32:33 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/20 18:23:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int8_t	exit_code = 0;

/* void redironly_cmd(t_cmd *cmd)
{
	ssize_t	ret;
	char	buf[BUFFER_SIZE];

	ret = read(cmd->redir_in, buf, BUFFER_SIZE);
	if (ret < 0)
		exit(exec_error("read: ", strerror(errno)));
	while (ret > 0)
	{
		write(cmd->redir_out, buf, ret);
		ret = read(cmd->redir_in, buf, BUFFER_SIZE);
		if (ret < 0)
			exit(exec_error("read: ", strerror(errno)));
	}
	exit(EXIT_SUCCESS);
} */

static void	exec_cmd(t_sh *sh, t_cmd *cmd)
{
	cmd->env = get_env_tab(sh->env);
	cmd->possible_paths = get_path_tab(sh->env);
	if (cmd->name && cmd->possible_paths)
	{
		if (access(cmd->name, X_OK) != -1)
			execve(cmd->name, cmd->args, cmd->env);
		else if (find_path(cmd, cmd->possible_paths))
		{
			execve(cmd->path, cmd->args, cmd->env);
			exit_code = NOT_EXECUTABLE;
		}
		else
			exit_code = NOT_FOUND;
	}
/* 	else if (cmd->args && !cmd->name && cmd->redir_out != NO_REDIR)
		redironly_cmd(cmd); */
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
