/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 00:25:15 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 17:57:58 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->index = 0;
	cmd->built_i = -1;
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->redir_error = 0;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*build_cmd(t_sh *sh, t_list *token, size_t i)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	set_cmd_params(sh, token, cmd);
	if (cmd->redir_in && cmd->redir_in->heredoc_ctrlc)
	{
		clear_cmd(cmd);
		free(cmd);
		return (NULL);
	}
	if (cmd->args)
	{
		cmd->built_i = is_builtin(cmd->args[0]);
		cmd->index = i;
		return (cmd);
	}
	return (cmd);
}
