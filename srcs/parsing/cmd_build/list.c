/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:37:25 by user42            #+#    #+#             */
/*   Updated: 2022/08/14 00:25:08 by nfauconn         ###   ########.fr       */
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
	size_t	i;
	t_cmd	*new_cmd;

	i = 0;
	while (token)
	{
		new_cmd = build_cmd(sh, token, i);
		if (!new_cmd)
			return (1);
		add_cmd_to_list(&sh->cmd_list, new_cmd);
		i++;
		while (token && !is_sep_operator(token->type))
			token = token->next;
		if (token && is_sep_operator(token->type))
			token = token->next;
	}
	sh->cmd_nb = i + 1;
	return (0);
}
