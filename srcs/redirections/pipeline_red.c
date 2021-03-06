/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:29:41 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/30 20:06:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static void	dup_output(t_cmd*cmd, int p[2])
{
	if (cmd->redir_out > -1)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(p[1], STDOUT_FILENO);
	close(p[1]);
}

static void	dup_input(t_cmd *cmd, int fd_in)
{
	if (cmd->redir_in > -1)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	else if (fd_in)
		dup2_close_old(fd_in, STDIN_FILENO);
}

void	pipeline_redir(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	int	error;

	(void)sh;
	error = 0;
	if (cmd->access_error)
		error = WRONG_REDIR;
	else
		error = open_redir(cmd);
	if (error)
	{
		close(p[1]);
		exit_clear_child(sh, error);
	}
	dup_input(cmd, fd_in);
	dup_output(cmd, p);
}
