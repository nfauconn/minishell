/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:43:10 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 23:11:49 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*trimed_s;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_checkset(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_checkset(set, s1[len - 1]))
		len--;
	trimed_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!trimed_s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trimed_s[i] = s1[i];
		i++;
	}
	trimed_s[i] = '\0';
	return (trimed_s);
}
