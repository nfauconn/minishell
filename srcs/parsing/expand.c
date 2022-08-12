/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 21:55:42 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*expand(char *token, t_sh *sh)
{
	char	*start;
	char	*to_add;
	size_t	new_size;
	char	*ret;

	new_size = 0;
	ret = NULL;
 	while (*token)
	{
		if (*token == '$' || is_quote(*token))
		{
			if (*token == '$' && is_quote(*(token + 1)))
				to_add = expand_doll_quotes_increment_tok(&token, sh);
			else if (*token == '$')
				to_add = expand_str_increment_tok(&token, sh);
			else if (is_quote(*token))
				to_add = expand_quotes_increment_tok(&token, sh);
			if (to_add)
			{
				new_size += ft_strlen(to_add);
				ret = ft_realloc_str(ret, new_size + 1);
				ft_strlcat(ret, to_add, new_size + 1);
			}
		}
		start = token;
		while (*token && !is_quote(*token) && *token != '$')
			token++;
		new_size += token - start;
		ret = ft_realloc_str(ret, new_size);
		ft_strlcat(ret, start, new_size + 1);
	}
	return (ret);
}
