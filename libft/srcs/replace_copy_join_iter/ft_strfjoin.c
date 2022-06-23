/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:56:56 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/11 09:42:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strfjoin(char **to_free, char *to_add)
{
	char	*tmp;

	if (!to_free)
		return ;
	tmp = *to_free;
	*to_free = ft_strjoin(*to_free, to_add);
	free(tmp);
}
