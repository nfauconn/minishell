/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:30:54 by noe               #+#    #+#             */
/*   Updated: 2022/08/19 13:48:51 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarraydup(char **strarray)
{
	char	**ret;
	ssize_t	size;
	size_t	i;

	size = ft_strarraysize(strarray);
	if (size < 0)
		return (NULL);
	ret = (char **)malloc(sizeof (char *) * (size + 1));
	i = 0;
	while (strarray[i])
	{
		ret[i] = ft_strdup(strarray[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
