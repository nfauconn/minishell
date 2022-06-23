/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_mx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:27:43 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/26 13:35:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	conv_mx(va_list *ap, t_conv *conv)
{
	size_t	len;
	int		i;

	i = 0;
	if (conv->hashtag)
		conv_p(ap, conv);
	else
		conv_x(ap, conv);
	len = conv->len;
	while (len--)
	{
		conv->str[i] = ft_toupper(conv->str[i]);
		i++;
	}
}
