/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:37:25 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 00:37:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	get_cmd_tab_sz(t_list *token)
{
	size_t	count;

	count = 0;
	while (token && !is_sep(token->type))
	{
		if ((token->type == WORD || is_quote(token->type))
			&& !is_blank(token->type))
			count++;
		token = token->next;
	}
	return (count);
}

size_t	get_cmd_nb(t_list *token)
{
	size_t	cmd_nb;

	cmd_nb = 1;
	while (token)
	{
		if (is_sep(token->type))
			cmd_nb++;
		token = token->next;
	}
	return (cmd_nb);
}

void	add_cmd_to_list(t_cmd **head, t_cmd *new)
{
	t_cmd	*curr;

	if (!*head)
	{
		*head = new;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

static char	**cmd_tab(t_list *token)
{
	char	**cmd_tab;
	size_t	size;
	size_t	i;

	size = get_cmd_tab_sz(token);
	cmd_tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cmd_tab)
		return (NULL);
	i = 0;
	while (token && !is_sep(token->type))
	{
		if (token->type == WORD)
		{
			cmd_tab[i] = ft_strdup((char *)token->content);
			while (token->next && token->next->type == WORD)
			{
				token = token->next;
				ft_strfjoin(&cmd_tab[i], (char *)token->content);
			}
			i++;
		}
		token = token->next;
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

void	fill_cmd_infos(t_sh *sh, t_list *token, t_cmd *cmd)
{
	cmd->args = cmd_tab(token);
	if (cmd->args)
		cmd->name = cmd->args[0];
	cmd->built_i = is_builtin(cmd->name);
	fill_cmd_redir(sh, token, cmd);
}
