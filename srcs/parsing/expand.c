/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 19:35:43 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	expand(char *token, char **to_expand, t_sh *sh)
{
	char	*start;
	char	*to_add;
	size_t	new_size;

	new_size = 0;
	printf("token = %s\n", token);
 	while (*token)
	{
		if (*token == '$' || is_quote(*token))
		{
			if (*token == '$')
				to_add = expand_str_increment_tok(&token, sh);
			else if (is_quote(*token))
				to_add = expand_quotes_increment_tok(&token, sh);
			else if (*token == '$' && is_quote(*(token + 1)))
				to_add = expand_doll_quotes_increment_tok(&token, sh);
			if (to_add)
			{
				new_size += ft_strlen(to_add);
				*to_expand = ft_realloc_str(*to_expand, new_size + 1);
				ft_strlcat(*to_expand, to_add, new_size + 1);
			}
		}
		start = token;
		while (*token && !is_quote(*token) && *token != '$')
			token++;
		new_size += token - start;
		*to_expand = ft_realloc_str(*to_expand, new_size + 1);
		ft_strlcat(*to_expand, start, new_size + 1);
	}
	return (0);
}
