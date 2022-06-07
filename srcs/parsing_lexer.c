/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/06/07 19:47:43 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	lexer(t_list *token)
{
	char	*tok;

	while (token)
	{
		tok = (char *)token->content;
//		if (is_separator(sign) && ft_strlen((char *)token->content) > 2)
		if (is_separator(token->type) && ft_strlen(tok) > 1)
		{
			ft_printerror("minish: syntax error near unexpected token `%c'\n", token->type);
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