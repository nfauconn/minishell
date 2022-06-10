/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_to_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:44:34 by user42            #+#    #+#             */
/*   Updated: 2022/06/09 17:45:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*tab_to_lst(char **tab)
{
	int		i;
	int		len;
	t_list	*lst;
	t_list	*new;

	len = 0;
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
