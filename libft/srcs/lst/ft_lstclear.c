/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:54:36 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 22:57:15 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*next;

	tmp = *lst;
	if (tmp)
		next = tmp->next;
	while (tmp)
	{
		if (tmp->content)
			del(tmp->content);
		free(tmp);
		tmp = next;
		if (tmp)
			next = tmp->next;
	}
	*lst = NULL;
}
