/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/06/11 11:29:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	check_nb_sign(t_list *token, size_t len)
{
	char	*tok;

	tok = (char *)token->content;
	if (is_redir(*tok))
	{
		if (token->type == IN_REDIR && len > 2)
			return(lex_error("<<"));
		else if (token->type == OUT_REDIR && len > 2)
			return (lex_error(">>"));
	}
	else if (is_separator(*tok))
	{
		if (token->type == PIPE && len > 1)
			return (lex_error("|"));
	}
	return (SUCCESS);
}

int	lexer(t_list *token)
{
	char	*tok;
	size_t	len;

	if (token && token->type == PIPE)
		return(lex_error("|"));
	while (token)
	{
		tok = (char *)token->content;
		len = ft_strlen(tok);
		if (is_redir(token->type) || is_separator(token->type))
		{
			if (check_nb_sign(token, len) == FAILURE)
				return (FAILURE);
			token = token->next;
			if (token)
			{
				if (is_redir(token->type) || is_separator(token->type))
				{
					len = ft_strlen((char *)token->content);
					if (check_nb_sign(token, len) == FAILURE)
						return (FAILURE);
					else
						return (lex_error((char *)token->content));
				}
			}
			else if (!token)
				return (lex_error("newline"));
		}
		token = token->next;
	}
	return (SUCCESS);
}

/* while (token->type == BLANK)
**		token = token->next;
** if (token->type == PIPE)
**		syntax_error (car pipe en premier dans ligne de commande)
** 
*/

/* syntax error :
**		- chevron '<' x 4 ou +
**		- chevron '>' x 3 ou +
**		- chevron + pipe
**		- pipe at beginning / pipe at end
**		- pipe x 3 ou +
*/