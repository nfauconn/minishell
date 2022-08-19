/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:07:05 by user42            #+#    #+#             */
/*   Updated: 2022/08/19 13:24:09 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern unsigned char	g_last_status;

static void	child_job(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	signal_catching_mode(CHILD_PROCESS);
	close(p[0]);
	if (!cmd->args[0])
	{
		close(p[1]);
		exit_clear_child(sh, g_last_status);
	}
	dup_io_pipeline(sh, cmd, p, fd_in);
	if (cmd->built_i > -1)
		launch_forked_builtin(sh, cmd);
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
		if (*fd)
			close(*fd);
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
			return (error_display("pipe", strerror(errno), 0));
		pid = fork();
		if (pid < 0)
			return (error_display("fork", strerror(errno), 0));
		if (pid == 0)
			child_job(sh, cmd, p, fd_in);
		else
			parent_job(cmd, p, &fd_in);
		cmd = cmd->next;
	}
	wait_children(sh);
	signal_catching_mode(INTERACTIVE);
	return (0);
}
