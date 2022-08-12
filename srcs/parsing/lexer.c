/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/08/06 21:43:45 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_bool	check_nb_sign(char **tok, int type)
{
	char	*start;
	size_t	len;

	start = *tok;
	go_through_same_char(tok);
	len = *tok - start;
	if (type == '<' && len == 3)
		return (sh_perror("does not handle here words"));
	if (type == '<' && len > 3)
		return (lex_perror("<<"));
	if (type == '>' && len > 2)
		return (lex_perror(">>"));
	if (type == '|' && len == 2)
		return (sh_perror("does not handle double pipes"));
	if (type == '|' && len > 2)
		return (lex_perror("|"));
	return (0);
}

static t_bool	lex_redir(char *content)
{
	if (!*content)
		return (lex_perror("newline"));
	while (is_blank(*content))
		content++;
	if (*content == '|')
		return (lex_perror("|"));
	else if (is_rediroperator(*content))
	{
		if (check_nb_sign(&content, (int)*content) == SUCCESS)
		{
			content--;
			if (*content == '>')
				return (lex_perror(">"));
			else if (*content == '<')
				return (lex_perror("<"));
		}
	}	
	return (0);
}

static t_bool	tok_lexer(char *content, int type)
{
	if (is_operator(type))
	{
		if (check_nb_sign(&content, type) == FAIL)
			return (1);
		while (*content && is_blank(*content))
			content++;
	}
	if (!*content)
		return (0);
	else if (is_rediroperator(type) && lex_redir(content) == FAIL)
		return (1);
	return (0);
}

t_bool	lexer(t_list *token)
{
	if (token->type == '|')
		return (lex_perror("|"));
	while (token)
	{
		if (tok_lexer((char *)token->content, token->type) == SUCCESS)
		{
			if (token->type == '|' && !token->next)
				return (sh_perror("does not handle ending pipe"));			
			token = token->next;
		}	
		else
			return (1);

	}
	return (0);
}
