/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:20:43 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/26 15:15:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_width(t_conv *conv, char c)
{
	conv->len = conv->width;
	conv->str = ft_memalloc(conv->len + 1);
	ft_memset(conv->str, ' ', conv->len);
	if (conv->left)
		conv->str[0] = c;
	else
	{
		if (conv->zero_padded)
			ft_memset(conv->str, '0', conv->len);
		conv->str[conv->len - 1] = c;
	}
}

void	conv_c(va_list *ap, t_conv *conv)
{
	unsigned char	c;

	c = (unsigned char)va_arg(*ap, int);
	if (conv->is_width && conv->width > 1)
		set_width(conv, c);
	else
	{
		conv->len = 1;
		conv->str = ft_memalloc(2);
		conv->str[conv->len - 1] = c;
	}
}
