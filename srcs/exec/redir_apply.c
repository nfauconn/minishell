/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:29:45 by user42            #+#    #+#             */
/*   Updated: 2022/07/13 15:36:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

/* static void	close_pipe_exit(char *s, int p[2])
{
	
} */

static void	open_redir(t_sh *sh, t_cmd *cmd, int p[2])
{
	errno = 0;
	cmd->redir_in = NO_REDIR;
	cmd->redir_out = NO_REDIR;
	if (cmd->redir_error)
	{
		error_display(cmd->redir_error, 0, 0);
		close(p[1]);
		exit_clear(sh, WRONG_REDIR);
	}
	if (cmd->infile)
	{
		cmd->redir_in = open(cmd->infile, O_RDONLY);
		if (cmd->redir_in == -1)
		{
			error_display(cmd->infile, strerror(errno), 0);
			close(p[1]);
			exit_clear(sh, WRONG_REDIR);
		}
	}
	if (cmd->outfile)
	{
		if (cmd->redir_out_type == APPEND_FILE)
			cmd->redir_out = open(cmd->outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			cmd->redir_out = open(cmd->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (cmd->redir_out == -1)
		{
			error_display(cmd->outfile, strerror(errno), 0);
			close(p[1]);
			exit_clear(sh, WRONG_REDIR);
		}
	}
}

void	redir_apply(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	open_redir(sh, cmd, p);
	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	else if (fd_in)
		dup2_close_old(fd_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(p[1], STDOUT_FILENO);
	close(p[1]);
}
