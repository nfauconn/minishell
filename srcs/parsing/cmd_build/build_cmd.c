/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 00:25:15 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/18 16:10:37 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_redir	init_redir(void)
{
	t_redir	new;

	new.filename = NULL;
	new.delim = NULL;
	new.fd = 0;
	new.is_heredoc = 0;
	new.quoted_delim = 0;
	new.is_append = 0;
	return (new);
}

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->index = 0;
	cmd->name = NULL;
	cmd->built_i = -1;
	cmd->args_tab = NULL;
	cmd->args_lst = NULL;
	cmd->possible_paths = NULL;
	cmd->path = NULL;
	cmd->envp = NULL;
	cmd->redir_in = init_redir();
	cmd->redir_out = init_redir();
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
	if (cmd->args_tab)
	{
		cmd->name = cmd->args_tab[0];
		cmd->built_i = is_builtin(cmd->name);
		cmd->index = i;
		return (cmd);
	}
	return (NULL);
}
