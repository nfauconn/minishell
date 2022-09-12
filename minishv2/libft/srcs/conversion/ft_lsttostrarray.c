/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttostrarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:47:20 by noe               #+#    #+#             */
/*   Updated: 2022/08/18 23:55:53 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lsttostrarray(t_list *lst)
{
	char	**tab;
	int		i;

	tab = (char **)malloc(sizeof (char *) * (ft_lstsize(lst) + 1));
	i = 0;
	while (lst)
	{
		tab[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
