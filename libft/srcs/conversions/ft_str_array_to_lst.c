/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_array_to_lst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:27:00 by user42            #+#    #+#             */
/*   Updated: 2022/06/19 13:41:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_str_array_to_lst(char **tab)
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
