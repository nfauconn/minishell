/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:50:25 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/08 12:51:11 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen_base(int nbr, int base)
{
	int	ret;

	ret = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		ret++;
	}
	nbr /= base;
	while (nbr)
	{
		nbr /= base;
		ret++;
	}
	return (ret);
}
