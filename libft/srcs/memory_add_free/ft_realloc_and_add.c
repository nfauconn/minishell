/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_and_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:16:21 by user42            #+#    #+#             */
/*   Updated: 2022/06/23 17:39:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc_and_add(char *buffer, char *to_add, size_t len)
{
	size_t	old_len;
	char	*new;

	if (to_add == NULL)
		return (buffer);
	if (buffer != NULL)
		old_len = ft_strlen(buffer);
	else
		old_len = 0;
	new = (char *)malloc(sizeof(char) * (len + old_len + 1));
	if (!new)
	{
		free(buffer);
		return (NULL);
	}
	if (old_len)
		ft_strlcpy(new, buffer, old_len + 1);
	ft_strlcpy(new + old_len, to_add, len + 1);
	free(buffer);
	return (new);
}
