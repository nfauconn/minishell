/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:07:05 by user42            #+#    #+#             */
/*   Updated: 2022/07/09 16:24:49 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	builtin_pipe_exec(t_sh *sh, t_cmd *cmd)
{
	int	ret;

	if ((cmd->built_i == cd || cmd->built_i == export || cmd->built_i == unset)
		&& cmd->next)
		ret = 0;
	else
		ret = sh->exec_built[cmd->built_i](sh, cmd);
/* 	close(STDIN_FILENO);
	close(STDOUT_FILENO); */
	clear_sh(sh);
	exit(ret);
}

static void	child_seq(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	signal_catching_mode(CHILD_PROCESS);
	close(p[0]);
	if (!cmd->name)
	{
		close(p[1]);
		exit(0);
	}
	redir_apply(cmd, p, fd_in);
	if (cmd->built_i > -1)
		builtin_pipe_exec(sh, cmd);
	else
		cmd_execve(sh, cmd);
}

static void	parent_seq(t_cmd *cmd, int p[2], int *fd)
{
	if (!cmd->next)
	{
		close(p[0]);
		close(p[1]);
		close(*fd);
	}
	else
	{
		close(p[1]);
		close_if_no_std(*fd);
		*fd = p[0];
	}
}

int	launch_pipeline(t_sh *sh, t_cmd *cmd)
{
	int		p[2];
	int		fd_in;
	pid_t	pid;

	fd_in = 0;
	signal_catching_mode(SH_PROCESS);
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
			parent_seq(cmd, p, &fd_in);
		cmd = cmd->next;
	}
	wait_children(sh);
	signal_catching_mode(INTERACTIVE);
	return (sh->last_status);
}
