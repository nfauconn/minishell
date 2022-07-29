/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/07/29 22:44:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_nb_sign(t_list *token)
{
	size_t	len;
	char	*tok;

	tok = (char *)token->content;
	len = ft_strlen(tok);
	if (token->type == '<' && len > 2)
		return (lex_error("<<"));
	if (token->type == '>' && len > 2)
		return (lex_error(">>"));
	if (token->type == PIPE && len > 1)
		return (lex_error("|"));
	return (SUCCESS);
}

static int	next_token_error(t_list *token)
{
	if (check_nb_sign(token) == FAILURE)
		return (FAILURE);
	return (lex_error((char *)token->content));
}

static int	tok_lexer(t_list *token)
{
	if (is_rediroperator(token->type))
	{
		if (check_nb_sign(token) == FAILURE)
			return (FAILURE);
		skip_token(&token, BLANK);
		if (token && (is_rediroperator(token->type) || is_sep(token->type)))
			return (next_token_error(token));
		else if (!token)
			return (lex_error("newline"));
	}
	else if (is_sep(token->type))
	{
		if (check_nb_sign(token) == FAILURE)
			return (FAILURE);
		skip_token(&token, BLANK);
		if (token && is_sep(token->type))
			return (next_token_error(token));
		else if (!token)
			return (lex_error("newline"));
	}
	return (SUCCESS);
}

int	lexer(t_list *token)
{
	token->type = *(char *)token->content;
	if (token->type == PIPE)
		return (lex_error("|"));
	while (token)
	{
		token->type = *(char *)token->content;
		if (tok_lexer(token) == SUCCESS)
			token = token->next;
		else
			return (FAILURE);
	}
	return (SUCCESS);
}
