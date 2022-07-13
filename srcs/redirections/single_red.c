/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:40:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/13 20:44:39 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

int	open_single_cmd_redir(t_cmd *cmd)
{
	errno = 0;
	cmd->redir_in = NO_REDIR;
	cmd->redir_out = NO_REDIR;
	if (cmd->redir_error)
	{
		error_display(cmd->redir_error, 0, 0);
		return (1);;
	}
	if (cmd->infile)
	{
		cmd->redir_in = open(cmd->infile, O_RDONLY);
		if (cmd->redir_in == WRONG_REDIR)
		{
			error_display(cmd->infile, strerror(errno), 0);
			return (1);;
		}
	}
	if (cmd->outfile)
	{
		if (cmd->redir_out_type == APPEND_FILE)
			cmd->redir_out = open(cmd->outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			cmd->redir_out = open(cmd->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (cmd->redir_out == WRONG_REDIR)
		{
			error_display(cmd->outfile, strerror(errno), 0);
			return (1);;
		}
	}
	return (0);
}

void	single_cmd_redir(t_sh *sh, t_cmd *cmd)
{
	if (open_single_cmd_redir(cmd) == FAILURE)
		exit_clear(sh, WRONG_REDIR);
	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
}