/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:25:56 by noe               #+#    #+#             */
/*   Updated: 2022/08/19 16:18:40 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern uint8_t	g_last_status;

static int	no_args(t_cmd *cmd)
{
	if (cmd->args[0] && !cmd->args[1])
		return (1);
	return (0);
}

static t_bool	not_executable_in_pipeline(t_cmd *cmd, char built_i)
{
	if ((built_i == cd || (built_i == export && !no_args(cmd))
			|| built_i == unset))
		return (1);
	return (0);
}

void	launch_forked_builtin(t_sh *sh, t_cmd *cmd)
{
	int	ret;

	if (not_executable_in_pipeline(cmd, cmd->built_i))
		ret = 0;
	else
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
	if (cmd->redir_in.fd == NO_REDIR)
		cmd->redir_in.fd = STDIN_FILENO;
	if (cmd->redir_out.fd == NO_REDIR)
		cmd->redir_out.fd = STDOUT_FILENO;
	g_last_status = sh->exec_built[cmd->built_i](sh, cmd);
}
