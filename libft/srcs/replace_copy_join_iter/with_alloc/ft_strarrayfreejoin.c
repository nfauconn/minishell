/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrayfreejoin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:08:21 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/09 21:16:27 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrayfreejoin(char ***prev, char ***to_join)
{
	char	**new;
	int		new_size;
	int		i;
	int		j;

	if (!*prev || !*to_join)
		return (NULL);
	new_size = ft_strarraysize(*prev) + ft_strarraysize(*to_join);
	new = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new)
		new = NULL;
	else
	{
		i = 0;
		j = -1;
		while ((*prev)[++j])
			new[i++] = ft_strdup((*prev)[j]);
		j = -1;
		while ((*to_join)[++j])
			new[i++] = ft_strdup((*to_join)[j]);
		new[i] = NULL;
	}
	ft_strarrayclear(prev);
	ft_strarrayclear(to_join);
	return (new);
}
