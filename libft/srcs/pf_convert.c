/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:59:17 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/26 13:35:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	convert(va_list *ap, t_pf *pf)
{
	t_conv	conv;

	init_conv(&conv);
	parse_flag(pf, &conv, ap);
	if (parse_conv(pf) != -1)
	{
		pf->fun_ptr[pf->index_conv](ap, &conv);
		insert_into_buffer(pf, conv.str, conv.len);
		free(conv.str);
		conv.str = NULL;
	}
}
