/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_forked_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:32:29 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/27 20:32:48 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern unsigned char	g_last_status;

static int	no_args(t_cmd *cmd)
{
	if (cmd->name && !cmd->args[1])
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
	exit(ret);
}

void	launch_single_builtin(t_sh *sh, t_cmd *cmd)
{
	if (open_redir(cmd) == FAILURE)
	{
		g_last_status = WRONG_REDIR;
		return ;
	}
	if (cmd->redir_in == NO_REDIR)
		cmd->redir_in = STDIN_FILENO;
	if (cmd->redir_out == NO_REDIR)
		cmd->redir_out = STDOUT_FILENO;
	g_last_status = sh->exec_built[cmd->built_i](sh, cmd);
}
