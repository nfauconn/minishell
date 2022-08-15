/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reallocstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:09:55 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/16 00:53:09 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_reallocstr(char *str, size_t newlen)
{
	char	*new_str;
	size_t	oldlen;

	new_str = NULL;
	if (!str)
		oldlen = 0;
	else
		oldlen = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * newlen + 1);
	if (!new_str)
		return (NULL);
	if (oldlen)
	{
		ft_memcpy(new_str, str, oldlen + 1);
		ft_bzero(new_str + oldlen, newlen + 1 - oldlen + 1);
		free(str);
	}
	else
	{
		ft_bzero(new_str, newlen + 1);
		free(str);
	}
	return (new_str);
}
