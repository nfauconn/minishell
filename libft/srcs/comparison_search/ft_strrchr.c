/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:23:13 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 23:09:52 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	to_find;
	int		len;
	char	*s1;

	to_find = (char)c;
	s1 = (char *)s;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (len >= 0)
	{
		if (s1[len] == to_find)
			return (&s1[len]);
		len--;
	}
	return (NULL);
}
