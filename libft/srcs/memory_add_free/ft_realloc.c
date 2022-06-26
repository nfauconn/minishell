/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:09:55 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/26 19:41:50 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*new_ptr;
	size_t	oldsize;

	new_ptr = NULL;
	if (!ptr)
		return (ft_memalloc(newsize));
	oldsize = ft_strlen(ptr);
	if (newsize <= oldsize)
		return (ptr);
	new_ptr = ft_memalloc(newsize);
	if (!new_ptr)
		return (ptr);
	ft_memcpy(new_ptr, ptr, oldsize);
	free(ptr);
	return (new_ptr);
}
