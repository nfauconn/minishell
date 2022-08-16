/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_io_singlecmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:40:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/16 09:00:04 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_bool	dup_io_singlecmd(t_cmd *cmd)
{
	int	error;

	error = 0;
	if (cmd->redir_error)
		error = WRONG_REDIR;
	else
		error = open_redir(cmd);
	if (error)
		return (1);
	if (cmd->redir_in.fd > -1)
		dup2_close_old(cmd->redir_in.fd, STDIN_FILENO);
	if (cmd->redir_out.fd > -1)
		dup2_close_old(cmd->redir_out.fd, STDOUT_FILENO);
	return (0);
}
