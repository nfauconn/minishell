/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:07:05 by user42            #+#    #+#             */
/*   Updated: 2022/07/24 17:50:20 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redir.h"

static int	no_args(t_cmd *cmd)
{
	if (cmd->name && !cmd->args[1])
		return (1);
	return (0);
}

static int	builtin_pipe_exec(t_sh *sh, t_cmd *cmd)
{
	int	ret;

	if ((cmd->built_i == cd || (cmd->built_i == export && !no_args(cmd))
		|| cmd->built_i == unset)
		&& cmd->next)
		ret = 0;
	else
		ret = sh->exec_built[cmd->built_i](sh, cmd);
	clear_sh(sh);
	exit(ret);
}

static void	child_job(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	signal_catching_mode(CHILD_PROCESS);
	close(p[0]);
	if (!cmd->name)
	{
		close(p[1]);
		exit(0);
	}
	pipeline_redir(sh, cmd, p, fd_in);
	if (cmd->built_i > -1)
		builtin_pipe_exec(sh, cmd);
	else
		cmd_execve(sh, cmd);
	signal_catching_mode(PARENT_PROCESS);
}

static void	parent_job(t_cmd *cmd, int p[2], int *fd)
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
	signal_catching_mode(PARENT_PROCESS);
	while (cmd)
	{
		if (pipe(p) < 0)
			return (exec_error("pipe: ", strerror(errno)));
		pid = fork();
		if (pid < 0)
			return (exec_error("fork: ", strerror(errno)));
		if (pid == 0)
			child_job(sh, cmd, p, fd_in);
		else
			parent_job(cmd, p, &fd_in);
		cmd = cmd->next;
	}
	wait_children(sh);
	signal_catching_mode(INTERACTIVE);
	return (sh->last_status);
}
