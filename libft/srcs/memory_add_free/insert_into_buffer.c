/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_into_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:16:21 by user42            #+#    #+#             */
/*   Updated: 2022/06/23 19:43:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	insert_into_buffer(char *buffer, char *to_add, size_t len)
{
	size_t	old_len;
	char	*new;

	if (!to_add)
		return ;
	if (!buffer)
		old_len = 0;
	else
		old_len = ft_strlen(buffer);
	new = (char *)malloc(sizeof (char) * (old_len + len + 1));
	if (!new)
		return ;
	if (old_len)
		ft_strlcpy(new, buffer, old_len + 1);
	ft_strlcpy(new + old_len, to_add, len + 1);
	free(buffer);
	buffer = new;
}

/*
char	*insert_into_buffer(char *buffer, char *to_add, size_t len)
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

*/