/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:50:29 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/26 13:35:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_width(t_conv *conv, size_t *to_copy)
{
	if (conv->is_width && conv->width > conv->len)
	{
		conv->len = conv->width;
		conv->str = ft_memalloc(conv->len + 1);
		if (!conv->left)
			conv->nb_s = conv->width - *to_copy;
		if (conv->zero_padded && !conv->left)
			ft_memset(conv->str, '0', conv->len);
		else
			ft_memset(conv->str, ' ', conv->len);
	}
	else
		conv->str = ft_memalloc(*to_copy + 1);
}

void	conv_p(va_list *ap, t_conv *conv)
{
	char				*str;
	char				*tmp;
	void				*i;
	size_t				to_copy;

	tmp = NULL;
	i = (void *)va_arg(*ap, void *);
	str = ft_strdup("0x");
	tmp = ft_ulltoa_base((t_ull)i, 16, 0);
	ft_strfjoin(&str, tmp);
	free(tmp);
	conv->len = ft_strlen(str);
	to_copy = conv->len;
	fill_width(conv, &to_copy);
	ft_memcpy(conv->str + conv->nb_s, str, to_copy);
	free(str);
}
