/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:40:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/27 20:21:18 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

int	single_cmd_redir(t_cmd *cmd)
{
	if (open_redir(cmd) == 1)
		return (1);
	if (cmd->redir_in > -1)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	if (cmd->redir_out > -1)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
	return (0);
}
