/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:35:30 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 19:35:31 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*expand_doll_quotes_increment_tok(char **token, t_sh *sh)
{
	char	quote;
	char	*new;

	quote = *((*token) + 1);
	new = expand_quotes(*token, sh);
	(*token) += 2;
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
	return (str);
}