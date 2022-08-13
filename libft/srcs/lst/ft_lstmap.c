/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:55:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 22:55:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		flag;
	t_list	*last;
	t_list	*first;

	flag = 1;
	if (!lst)
		return (NULL);
	first = ft_lstnew(f(lst->content));
	if (!first)
		return (NULL);
	last = first;
	lst = lst->next;
	while (lst && flag > 0)
	{
		last->next = ft_lstnew(f(lst->content));
		if (!last->next)
		{
			ft_lstclear(&first, del);
			flag = -1;
		}
		lst = lst->next;
		last = last->next;
	}
	return (first);
}
