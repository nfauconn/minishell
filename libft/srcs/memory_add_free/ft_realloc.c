/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:09:55 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 16:08:38 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	void	*new_ptr;
	size_t	oldsize;

	new_ptr = NULL;
	if (!ptr)
		return (ft_memalloc(newsize));
	oldsize = sizeof(ptr);
	if (newsize <= oldsize)
		return (ptr);
	new_ptr = ft_memalloc(newsize);
	if (!new_ptr)
		return (ptr);
	ft_memcpy(new_ptr, ptr, oldsize);
	free(ptr);
	return (new_ptr);
}

char	*ft_realloc_str(char *str, size_t newsize)
{
	char	*new_str;
	size_t	oldsize;

	new_str = NULL;
	if (!str)
		return ((char *)malloc(sizeof(char) * (newsize + 1)));
	oldsize = ft_strlen(str);
	if (newsize <= oldsize)
		return (str);
	new_str = (char *)malloc(sizeof(char) * (newsize + 1));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, oldsize);
	new_str[oldsize] = '\0';
	free(str);
	return (new_str);
}
