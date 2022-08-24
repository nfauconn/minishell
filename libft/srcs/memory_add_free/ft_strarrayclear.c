/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrayclear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:28:54 by user42            #+#    #+#             */
/*   Updated: 2022/08/24 21:20:51 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarrayclear(char ***tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while ((*tab)[i])
		free((*tab)[i++]);
	free(*tab);
	*tab = NULL;
}
