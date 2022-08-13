/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:35:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 22:32:57 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*expand_quotes(char *ptr, t_sh *sh)
{
//	bool	quote;
//	char	*start;
	char	*new;
//	char	*tmp;

//	quote = sizeof(char);
	new = NULL;
/* 	if (*ptr == '$')
		ptr++; */
//	start = ptr + quote;
//	if (ft_strlen(ptr) == quote + quote)
//		new = ft_strdup("");
/* 	else  */if (*ptr == QUOTE)
		new = ft_substr(ptr, 0, ft_strlen(ptr));// - quote);
	else if (*ptr == DB_QUOTE)
	{
/* 		tmp = expand_string(start, sh);
		printf("tmp = %s\n", tmp);
		new = ft_substr(tmp, 0, ft_strlen(tmp) - quote);
		free(tmp); */
		new = expand_string(ptr, sh);
	}
	return (new);
}
