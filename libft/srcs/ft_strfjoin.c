/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:56:56 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/08 10:31:56 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strfjoin(char **over, char *buff)
{
	char	*tmp;

	if (!over)
		return ;
	tmp = *over;
	*over = ft_strjoin(*over, buff);
	free(tmp);
}
