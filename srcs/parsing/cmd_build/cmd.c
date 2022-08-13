/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 00:25:15 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/14 00:40:09 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd	*build_cmd(t_sh *sh, t_list *token, size_t i)
{
	(void)sh;
	t_cmd	*cmd;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	if (get_args_and_redir(sh, token, cmd))
		return (NULL);
	else
		cmd->name = cmd->args[0];
	cmd->built_i = is_builtin(cmd->name);
	cmd->index = i;
	return (cmd);
}