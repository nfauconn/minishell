/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ft_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 23:07:14 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/26 13:35:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;
	t_pf	pf;

	init_pf(&pf, format);
	va_start(ap, format);
	ret = main_loop(&pf, &ap);
	va_end(ap);
	return (ret);
}
