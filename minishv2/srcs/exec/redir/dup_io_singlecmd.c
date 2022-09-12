/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_io_singlecmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:40:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 19:33:57 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_bool	dup_io_singlecmd(t_cmd *cmd)
{
	int	error;

	if (cmd->redir_error)
		error = WRONG_REDIR;
	else
		error = open_redir(cmd);
	if (error)
		return (1);
	if (cmd->redir_in && cmd->redir_in->fd > -1)
	{
		dup2(cmd->redir_in->fd, STDIN_FILENO);
		close(cmd->redir_in->fd);
	}
	if (cmd->redir_out)
	{
		while (cmd->redir_out && cmd->redir_out->next)
			cmd->redir_out = cmd->redir_out->next;
		if (cmd->redir_out->fd > -1)
		{
			dup2(cmd->redir_out->fd, STDOUT_FILENO);
			close(cmd->redir_out->fd);
		}
	}
	return (0);
}
