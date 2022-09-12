/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_d_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:22:49 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/26 13:35:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nb_to_array(t_conv *conv, char **str, int *i, size_t base)
{
	size_t	is_neg;

	is_neg = 0;
	if (*i < 0)
	{
		is_neg = 1;
		if (*i == -2147483648)
			*str = ft_strdup("2147483648");
		else
			*i = -(*i);
	}
	if (*i == 0 && conv->is_prec && conv->prec == 0)
		*str = ft_strdup("");
	else if (*i != -2147483648)
		*str = ft_ulltoa_base(*i, base, 0);
	return (is_neg);
}

static void	fill_sign(t_conv *conv, size_t is_neg, size_t *sign)
{
	*sign = 1;
	if (is_neg)
		conv->sign = '-';
	else if (conv->if_positive)
	{
		if (conv->if_positive > 2)
			conv->sign = '+';
		else
			conv->sign = ' ';
	}
}

void	conv_d_i(va_list *ap, t_conv *conv)
{
	int		i;
	char	*str;
	size_t	is_neg;
	size_t	sign;

	i = (long)va_arg(*ap, int);
	sign = 0;
	is_neg = nb_to_array(conv, &str, &i, 10);
	if (is_neg || conv->if_positive)
		fill_sign(conv, is_neg, &sign);
	conv->len = ft_strlen(str);
	if ((conv->prec <= conv->len) && (conv->width <= (conv->len + sign)))
	{
		fill_without_pw(conv, str, sign);
		free(str);
		return ;
	}
	spaces_zeros(conv, sign);
	conv->str = ft_memalloc(conv->len + conv->nb_s + sign + conv->nb_z + 1);
	fill_with_pw(conv, str, sign);
	free(str);
}
