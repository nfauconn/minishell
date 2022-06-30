/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:36:49 by user42            #+#    #+#             */
/*   Updated: 2022/06/30 09:48:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_builtin_exec(t_sh *sh, t_cmd *cmd)
{
	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
	sh->last_status = sh->exec_built[cmd->built_i](sh, cmd);
	return (sh->last_status);
}
