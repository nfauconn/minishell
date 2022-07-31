/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:57:56 by user42            #+#    #+#             */
/*   Updated: 2022/07/31 19:05:47 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	skip_token(t_list **token, int to_skip)
{
	if (token && *token)
		*token = (*token)->next;
	(*token)->type = *(char *)(*token)->content;
	if (token && *token && (*token)->type == to_skip)
		*token = (*token)->next;
}

void	display_token_list(t_list *lst)
{
	while (lst)
	{
		printf("tok = %20s | type = %d\n", (char *)lst->content, lst->type);
		lst = lst->next;
	}
}

void	add_token_to_list(t_list **token_list, char *token)
{
	t_list	*new;

	new = ft_lstnew(token);
	new->type = *token;
	ft_lstadd_back(token_list, new);
}
