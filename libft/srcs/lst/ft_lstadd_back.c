/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:54:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 22:56:02 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elm;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	elm = *lst;
	while (elm->next)
		elm = elm->next;
	elm->next = new;
}
