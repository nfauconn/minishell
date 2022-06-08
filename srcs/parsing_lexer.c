/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/06/08 15:10:21 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	lexer(t_list *token)
{
	char	*tok;
	size_t	len;

	if (token->type == PIPE)
	{
		return(lex_error("|"));
	}
	while (token)
	{
		tok = (char *)token->content;
		len = ft_strlen(tok);
		if (is_separator(token->type))
		{
			if (token->type == IN_REDIR && len > 2)
				return(lex_error("<<"));
			else if (token->type == OUT_REDIR && len > 3)
				return (lex_error(">>"));
			if (!token->next)
				return (lex_error("new_line"));
			return (FAILURE);
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