/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:53:30 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/08 10:47:29 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*source;
	char	*lastd;
	char	*lasts;

	if (dst == NULL && src == NULL)
		return (NULL);
	dest = (char *)dst;
	source = (char *)src;
	if (dest < source)
	{
		while (len--)
			*dest++ = *source++;
	}
	else
	{
		lastd = dest + (len - 1);
		lasts = source + (len - 1);
		while (len--)
			*lastd-- = *lasts--;
	}
	return (dst);
}
