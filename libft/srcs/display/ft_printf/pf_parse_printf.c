/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:37:36 by nfauconn          #+#    #+#             */
/*   Updated: 2021/09/26 13:34:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_flags(t_pf *pf, t_conv *conv)
{
	char	c;

	c = *pf->ptr;
	while (c == '-' || c == '0' || c == '+' || c == ' ' || c == '#')
	{
		if (c == '-')
			conv->left = 1;
		if (c == '0')
			conv->zero_padded = 1;
		if (c == '+')
			conv->if_positive = 3;
		if (c == ' ' && conv->if_positive != 3)
			conv->if_positive = 2;
		if (c == '#')
			conv->hashtag = 1;
		pf->ptr++;
		c = *pf->ptr;
	}
}

static void	set_width(t_pf *pf, t_conv *conv, va_list *ap)
{
	int		w;

	conv->is_width = 1;
	if (*pf->ptr == '*')
	{
		w = (int)va_arg(*ap, int);
		if (!w)
			conv->width = 0;
		if (w < 0)
		{
			conv->left = 1;
			conv->width = -w;
		}
		else
			conv->width = w;
		pf->ptr++;
	}
	else
		while (*pf->ptr && ft_isdigit(*pf->ptr))
			conv->width = (conv->width * 10) + (*pf->ptr++ - '0');
}

static void	set_prec(t_pf *pf, t_conv *conv, va_list *ap)
{
	int		p;

	conv->is_prec = 1;
	pf->ptr++;
	if (*pf->ptr == '*')
	{
		p = (int)va_arg(*ap, int);
		if (!p)
			conv->prec = 0;
		if (p < 0)
			conv->is_prec = 0;
		else
			conv->prec = p;
		pf->ptr++;
	}
	else
		while (*pf->ptr && ft_isdigit(*pf->ptr))
			conv->prec = (conv->prec * 10) + (*pf->ptr++ - '0');
}

void	parse_flag(t_pf *pf, t_conv *conv, va_list *ap)
{
	while (*pf->ptr && (ft_isflagpf(*pf->ptr) || ft_isdigit(*pf->ptr)))
	{
		if (*pf->ptr == '-' || *pf->ptr == '0' || *pf->ptr == '+')
			set_flags(pf, conv);
		if (*pf->ptr == ' ' || *pf->ptr == '#')
			set_flags(pf, conv);
		if (ft_isdigit(*pf->ptr) || *pf->ptr == '*')
			set_width(pf, conv, ap);
		if (*pf->ptr == '-' || *pf->ptr == '+')
			set_flags(pf, conv);
		if (*pf->ptr == ' ' || *pf->ptr == '#')
			set_flags(pf, conv);
		if (*pf->ptr == '.')
			set_prec(pf, conv, ap);
	}
}

int	parse_conv(t_pf *pf)
{
	int	i;

	i = 0;
	while (*pf->ptr && CONV[i])
	{
		if (CONV[i] == *pf->ptr)
		{
			pf->index_conv = i;
			pf->ptr++;
			return (i);
		}
		i++;
	}
	return (-1);
}
