/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:29:45 by user42            #+#    #+#             */
/*   Updated: 2022/07/12 22:52:30 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

static void	open_redir(t_cmd *cmd)
{
	errno = 0;
	cmd->redir_in = NO_REDIR;
	cmd->redir_out = NO_REDIR;
	if (cmd->redir_error)
	{
		error_display(cmd->redir_error, 0, 0);
		return ;
	}
	if (cmd->infile)
		cmd->redir_in = open(cmd->infile, O_RDONLY);
	if (cmd->outfile)
	{
		if (cmd->redir_out_type == APPEND_FILE)
			cmd->redir_out = open(cmd->outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			cmd->redir_out = open(cmd->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
}

void	redir_apply(t_cmd *cmd, int p[2], int fd_in)
{
	open_redir(cmd);
	if (cmd->redir_error)
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
	{
		#ifdef DEBUG
		ft_printerror ("dup2           : %d becomes %d\n", p[1], STDOUT_FILENO);
		#endif
		dup2(p[1], STDOUT_FILENO);
	}
	close(p[1]);
}
