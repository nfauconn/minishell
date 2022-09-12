/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraytolist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:12:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/19 15:01:41 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_strarraytolist(char **tab)
{
	int		i;
	int		len;
	t_list	*lst;
	t_list	*new;

	len = 0;
	if (!tab)
		return (NULL);
	while (tab[len])
		len++;
	lst = NULL;
	i = 0;
	while (tab[i])
	{
		new = (t_list *)malloc(sizeof(t_list));
		new->content = ft_strdup(tab[i]);
		new->next = NULL;
		ft_lstadd_back(&lst, new);
		i++;
	}
	return (lst);
}
