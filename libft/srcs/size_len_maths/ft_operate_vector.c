/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operate_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:26:13 by user42            #+#    #+#             */
/*   Updated: 2022/06/23 15:44:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_v	ft_operate_vector(t_v vector, char operation, int nb)
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
