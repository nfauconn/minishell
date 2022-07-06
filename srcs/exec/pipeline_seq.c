/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:32:33 by mdankou           #+#    #+#             */
/*   Updated: 2022/07/05 16:42:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_seq(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	signal_catching_mode(CHILD);
	redir_apply(cmd, p, fd_in);
	exec_cmd(sh, cmd);
}

void	parent_seq(t_cmd *cmd, int p[2], int *fd)
{
	if (!cmd->next)
	{
		close(p[0]);
		close(p[1]);
		close(*fd);
		return ;
	}
	close(p[1]);
	close_if_exists(*fd);
	*fd = p[0];
}

int	pipeline_seq(t_sh *sh, t_cmd *cmd)
{
	int		p[2];
	int		fd_in;
	pid_t	pid;

	fd_in = 0;
	signal_catching_mode(PGM_EXEC);
	while (cmd)
	{
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
