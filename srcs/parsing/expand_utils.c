/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:35:30 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 21:42:14 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*expand_doll_quotes_increment_tok(char **token, t_sh *sh)
{
	char	quote;
	char	*new;

	(*token)++;
	quote = **token;
	new = expand_quotes(*token, sh);
	(*token)++;
	while (**token && **token != quote)
		(*token)++;
	(*token)++;
	return (new);
}

char	*expand_quotes_increment_tok(char **token, t_sh *sh)
{
	char	quote;
	char	*new;

	quote = **token;
	new = expand_quotes(*token, sh);
	(*token)++;
	while (**token && **token != quote)
		(*token)++;
	(*token)++;
//	printf("new = %s | *token = %s\n", new, *token);
	return (new);
}

char	*expand_str_increment_tok(char **token, t_sh *sh)
{
	char	*str;

	str = expand_string(*token, sh);
	(*token)++;
	while (**token 
		&& !is_blank(**token) && !is_quote(**token) && **token != '$')
		(*token)++;
/* 	if (is_quote(**token))
		expand_quotes_increment_tok(token, sh);
	if (**token == '$')
		expand */
	return (str);
}