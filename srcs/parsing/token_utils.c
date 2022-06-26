/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:57:56 by user42            #+#    #+#             */
/*   Updated: 2022/06/26 23:01:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_token(t_list *token, int to_skip)
{
	if (token)
		token = token->next;
	if (token && token->type == to_skip)
		token = token->next;
	return (token);
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
	ft_lstadd_back(token_list, new);
}
