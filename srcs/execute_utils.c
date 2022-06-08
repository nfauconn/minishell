/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:38:14 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/08 15:20:20 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void grab_command(t_list *token)
{
	t_list *l;
	t_list	*start;

	while (token)
	{
		if (token->type == IN_REDIR || token->type == OUT_REDIR)
		{
			start = token->next->next;
			if (start)
			while (start && !is_separator(*(char *)start->content)
				&& !!is_blank(*(char *)start->content))
			{
				ft_lstadd_back(&l, ft_lstnew(ft_strdup(start->content)));
				start = start->next;
			}
		}
		else
			start = token->next;
		token = start;
	}
	ft_lstiter(l, display_token_list);
}