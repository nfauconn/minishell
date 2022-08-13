/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:35:23 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 21:41:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*expand_string(char *ptr, t_sh *sh)
{
	char	*var_val;
	char	*new;
	size_t	new_size;
	char	*start;

	var_val = NULL;
	new = NULL;
	new_size = 0;
 	while (*ptr)
	{
		if (*ptr == '$')
		{
			ptr++;
			var_val = expanded_content(&ptr, sh);
//			printf("var_val = %s\n", var_val);
			if (var_val)
			{
				new_size += ft_strlen(var_val);
				new = ft_realloc_str(new, new_size + 1);
				ft_strlcat(new, var_val, new_size + 1);
				ft_strdel(&var_val);
			}
			else
			{
				new = ft_realloc_str(new, new_size + 1);
			}
//			printf("new = %s | new_size = %zu | ptr = %s\n", new, new_size, ptr);
		}
/* 		else
		{ */
			start = ptr;
			while (*ptr && *ptr != '$') // what if quotes ???? (attention cat expand quotes l appelle btw)
				ptr++;
			new_size += ptr - start;
			new = ft_realloc_str(new, new_size + 1);
			ft_strlcat(new, start, new_size + 1);
//			printf("new = %s | new_size = %zu | ptr = %s\n\n", new, new_size, ptr);
/* 		} */
	}
	return (new);
}
