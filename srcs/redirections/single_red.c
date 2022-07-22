/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:40:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/21 22:13:36 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

void	single_cmd_redir(t_sh *sh, t_cmd *cmd)
{
	if (open_redir(cmd) == FAILURE)
		exit_clear(sh, WRONG_REDIR);
	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
}
