/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:25:56 by noe               #+#    #+#             */
/*   Updated: 2022/09/14 20:20:49 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern uint8_t	g_last_status;

void	launch_forked_builtin(t_sh *sh, t_cmd *cmd)
{
	int	ret;

	cmd->redir_out.fd = STDOUT_FILENO;
	ret = sh->exec_built[cmd->built_i](sh, cmd);
	exit_clear_child(sh, ret);
}

void	launch_single_builtin(t_sh *sh, t_cmd *cmd)
{
	if (open_redir(cmd) == FAIL)
	{
		g_last_status = WRONG_REDIR;
		return ;
	}
	if (sh->cmd_nb >1  || !cmd->redir_out.filename)
		cmd->redir_out.fd = STDOUT_FILENO;
	g_last_status = sh->exec_built[cmd->built_i](sh, cmd);
}
