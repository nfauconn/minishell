/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_fill_nb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 23:17:49 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/26 13:35:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	spaces_zeros(t_conv *conv, size_t sign)
{
	if (conv->prec <= conv->len && conv->width > (conv->len + sign))
	{
		conv->nb_s = conv->width - conv->len - sign;
		if (conv->zero_padded && !conv->left && !conv->is_prec)
		{
			conv->nb_z = conv->nb_s;
			conv->nb_s = 0;
		}
	}
	else if (conv->prec > conv->len)
	{
		if (conv->width > (conv->prec + sign))
			conv->nb_s = conv->width - conv->prec - sign;
		conv->nb_z = conv->prec - conv->len;
	}
}

void	fill_without_pw(t_conv *conv, char *str, size_t sign)
{
	conv->len += sign;
	conv->str = ft_memalloc(conv->len + 1);
	if (sign)
		ft_memset(conv->str, conv->sign, 1);
	ft_memcpy(conv->str + sign, str, conv->len);
}

void	fill_with_pw(t_conv *conv, const char *str, size_t sign)
{
	size_t	shift;

	if (conv->left)
	{
		if (sign)
			ft_memset(conv->str, conv->sign, 1);
		ft_memset(conv->str + sign, '0', conv->nb_z);
		ft_memcpy(conv->str + sign + conv->nb_z, str, conv->len);
		shift = sign + conv->nb_z + conv->len;
		ft_memset(conv->str + shift, ' ', conv->nb_s);
	}
	else
	{
		ft_memset(conv->str, ' ', conv->nb_s);
		if (sign)
			ft_memset(conv->str + conv->nb_s, conv->sign, 1);
		ft_memset(conv->str + conv->nb_s + sign, '0', conv->nb_z);
		shift = conv->nb_s + sign + conv->nb_z;
		ft_memcpy(conv->str + shift, str, conv->len + sign);
	}
	conv->len += conv->nb_s + sign + conv->nb_z;
}
