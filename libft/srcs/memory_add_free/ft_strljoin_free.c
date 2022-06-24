/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strljoin_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:04:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/24 11:58:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_new(char *s1, char const *s2, char *new, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i] && i < len)
	{
		new[j + i] = s2[i];
		i++;
	}
	new[j + i] = '\0';
	return (new);
}

void	ft_strljoin_free(char *s1, char const *s2, size_t len)
{
	char	*new;
	size_t	new_len;
	size_t	old_len;

	if (s1 && !s2)
	{
		free(s1);
		s1 = ft_strdup("");
		return ;
	}
	if (!s1)
		old_len = 0;
	else
		old_len = ft_strlen(s1);
	new_len = old_len + len;
	new = (char *)malloc(sizeof (char) * (new_len + 1));
	if (!new)
		return ;
	new = fill_new(s1, s2, new, len);
	if (s1)
		free(s1);
	s1 = new;
}
