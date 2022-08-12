/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:52:27 by user42            #+#    #+#             */
/*   Updated: 2022/08/12 11:38:14 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_redir	init_redir(void)
{
	t_redir	new;

/* 	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL); */
	new.filename = NULL;
	new.delim = NULL;
	new.fd = 0;
	new.is_heredoc = 0;
	new.quoted_delim = 0;
	new.is_append = 0;
//	new.is_ambig = 0;
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
	cmd->args = NULL;
	cmd->possible_paths = NULL;
	cmd->path = NULL;
	cmd->redir_in = init_redir();
	cmd->redir_out = init_redir();
	cmd->redir_error = 0;
	cmd->next = NULL;
	return (cmd);
}
