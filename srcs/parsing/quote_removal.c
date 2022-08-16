/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:20:06 by noe               #+#    #+#             */
/*   Updated: 2022/08/16 17:17:15 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*remove_quote(char *str)
{
	t_newstr	new;
	char		*start;
	char		quote;

	new.len = 0;
	quote = 0;
	new.str = NULL;
	while (*str)
	{
		start = str;
		while (*str
			&& !((!quote && is_quote(*str)) || (quote && *str == quote)))
			str++;
		if (!quote && is_quote(*str))
			quote = *str;
		else if (quote && *str == quote)
			quote = 0;
		new.len += str - start;
		new.str = ft_reallocstr(new.str, new.len);
		ft_strlcat(new.str, start, new.len + 1);
		if (is_quote(*str))
			start = ++str;
	}
	return (new.str);
}
