/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:58:14 by nfauconn          #+#    #+#             */
/*   Updated: 2022/04/27 19:07:36 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	nb_to_array(t_conv *conv, char **str, unsigned int *i)
{
	if (i == 0 && conv->is_prec && conv->prec == 0)
		*str = ft_strdup("");
	else
		*str = ft_ulltoa_base((t_ull)i, 16, 0);
}

void	conv_x(va_list *ap, t_conv *conv)
{
	unsigned int		*i;
	char				*str;

	if (conv->hashtag)
	{
		conv_p(ap, conv);
		return ;
	}
	i = (unsigned int *)va_arg(*ap, void *);
	nb_to_array(conv, &str, i);
	conv->len = ft_strlen(str);
	if (i != 0 && (conv->prec <= conv->len) && (conv->width <= (conv->len)))
	{
		fill_without_pw(conv, str, 0);
		free(str);
		return ;
	}
	spaces_zeros(conv, 0);
	conv->str = ft_memalloc(conv->len + conv->nb_s + conv->nb_z + 1);
	fill_with_pw(conv, str, 0);
	free(str);
}
