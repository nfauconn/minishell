/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:26:13 by user42            #+#    #+#             */
/*   Updated: 2021/10/14 18:40:24 by user42           ###   ########.fr       */
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

float	ft_negative_power(int nb, int power)
{
	float	res;

	power *= -1;
	res = 1 / ft_power(nb, power);
	return (res);
}

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

t_v	operate_vector(t_v vector, char operation, int nb)
{
	t_v	res;

	if (operation == '*')
	{
		res.x = vector.x * nb;
		res.y = vector.y * nb;
	}
	if (operation == '/')
	{
		res.x = vector.x / nb;
		res.y = vector.y / nb;
	}
	if (operation == '+')
	{
		res.x = vector.x + nb;
		res.y = vector.y + nb;
	}
	if (operation == '-')
	{
		res.x = vector.x - nb;
		res.y = vector.y - nb;
	}
	return (res);
}
