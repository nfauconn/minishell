/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:52:53 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/01 17:56:58 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *s, int base)
{
	unsigned long long	nbr;

	nbr = 0;
	while (*s)
	{
		nbr = (nbr * base) + (*s - '0');
		s++;
	}
	return ((int)(nbr));
}
