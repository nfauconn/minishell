/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:37:25 by user42            #+#    #+#             */
/*   Updated: 2022/08/15 00:58:38 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

bool	build_cmd_lst(t_sh *sh, t_list *token)
{
	size_t	cmd_index;
	t_cmd	*new_cmd;

	cmd_index = 0;
	while (token)
	{
		new_cmd = build_cmd(sh, token, cmd_index);
		if (!new_cmd)
			return (1);
		add_cmd_to_list(&sh->cmd_list, new_cmd);
		while (token && !is_sep_operator(token->type))
			token = token->next;
		if (token && is_sep_operator(token->type))
			token = token->next;
		cmd_index++;
	}
	sh->cmd_nb = cmd_index + 1;
	return (0);
}
