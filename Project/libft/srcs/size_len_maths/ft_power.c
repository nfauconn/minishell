/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:40:51 by user42            #+#    #+#             */
/*   Updated: 2022/06/23 15:41:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ull	ft_power(int nb, int power)
{
	int		i;
	t_ull	res;

	i = 1;
	if (power < 0)
		ft_putstr_fd("ft_power : for neg power, use ft_negative_power", 2);
	res = nb;
	while (i++ < power)
		res = res * nb;
	return (res);
}
