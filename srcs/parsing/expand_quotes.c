/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:35:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 19:35:20 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*expand_quotes(char *ptr, t_sh *sh)
{
	t_bool	quote;
	char	*start;
	char	*new;
	char	*tmp;

	quote = 1;
	new = NULL;
	if (*ptr == '$')
		ptr++;
	start = ptr + quote;
	if (ft_strlen(ptr) == quote + quote)
		new = ft_strdup("");
	else if (*ptr == QUOTE)
		new = ft_substr(start, 0, ft_strlen(start) - quote);
	else if (*ptr == DB_QUOTE)
	{
		tmp = expand_string(start, sh);
		new = ft_substr(tmp, 0, ft_strlen(tmp) - quote);
		free(tmp);
	}
	return (new);
}
