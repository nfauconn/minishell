/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/05/18 18:31:14 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	check_syntax_error(t_input *input, char	*token, char sign)
{
	if (sign == PIPE)
	{
		token++;
		if (*token == PIPE)
			clean_exit(input, "syntax error near unexpected token `|'");
	}
	
}

void	lexer(t_input *input, t_list *tok_l)
{
	char	sign;

	while (tok_l)
	{
		sign = *(char *)tok_l->content;
		if (is_meta(sign))
			check_syntax_error(input, (char *)tok_l->content, sign);
		tok_l = tok_l->next;
	}
}
