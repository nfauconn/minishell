/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_root.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:43:24 by user42            #+#    #+#             */
/*   Updated: 2022/06/23 15:43:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_square_root(int nb)
{
	int	res;
	int	previous_res;

	res = 1;
	if (nb < 0)
	{
		ft_putstr_fd("ft_square_root : arg must be an unsigned int\n", 2);
		return (0);
	}
	if (nb == 0)
		return (1);
	while (1)
	{
		if (res * res == nb)
			return (res);
		if (res * res > nb)
			return (previous_res);
		previous_res = res;
		res++;
	}
}
