/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:20:44 by mdankou           #+#    #+#             */
/*   Updated: 2021/12/08 16:11:32 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next;

	curr = *lst;
	if (curr)
		next = curr->next;
	while (curr)
	{
		del(curr->content);
		free(curr);
		curr = next;
		if (curr)
			next = curr->next;
	}
	*lst = NULL;
}
