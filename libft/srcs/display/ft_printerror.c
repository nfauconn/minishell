/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:53:47 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/24 10:41:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	printerror_main_loop(t_pf *pf, va_list *ap)
{
	while (*pf->format)
	{
		while (*pf->ptr && (*pf->ptr != '%'))
			pf->ptr++;
		insert_into_pf_buffer(pf, pf->format, pf->ptr - pf->format);
		if (*pf->ptr && *pf->ptr == '%')
		{
			pf->ptr++;
			convert(ap, pf);
		}
		pf->format = pf->ptr;
	}
	if (pf->buffer)
		write(STDERR_FILENO, pf->buffer, (pf->bufsize));
	free(pf->buffer);
	return ((int)pf->bufsize);
}

int	ft_printerror(const char *format, ...)
{
	va_list	ap;
	int		ret;
	t_pf	pf;

	init_pf(&pf, format);
	pf.fun_ptr[s] = &error_conv_s;
	va_start(ap, format);
	ret = printerror_main_loop(&pf, &ap);
	va_end(ap);
	return (ret);
}
