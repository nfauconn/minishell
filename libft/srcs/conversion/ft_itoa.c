/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:01:03 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 22:54:06 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_len(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*nombre;
	int		len;
	long	nb;

	nb = (long)n;
	len = nb_len(nb);
	nombre = (char *)malloc(sizeof(char) * (len + 1));
	if (!nombre)
		return (NULL);
	nombre[len--] = '\0';
	if (nb == 0)
		nombre[len] = '0';
	if (nb < 0)
	{
		nombre[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		nombre[len--] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (nombre);
}
