/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:51:09 by nfauconn          #+#    #+#             */
/*   Updated: 2021/10/04 11:27:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strfdup(char **over, char *buff)
{
	char	*tmp;

	if (!over)
		return ;
	tmp = *over;
	*over = ft_strdup(buff);
	free(tmp);
	tmp = NULL;
}
