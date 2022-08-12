/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:40:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 19:55:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

int	single_cmd_redir(t_cmd *cmd)
{
	if (open_redir(cmd) == 1)
		return (1);
	if (cmd->redir_in.fd > -1)
		dup2_close_old(cmd->redir_in.fd, STDIN_FILENO);
	if (cmd->redir_out.fd > -1)
		dup2_close_old(cmd->redir_out.fd, STDOUT_FILENO);
	return (0);
}
