/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/05/18 15:37:55 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	check_syntax_error(t_input *input, t_list *tok_l, char sign)
{
	t_list *tmp;

	tmp = tok_l;
	if (sign == PIPE)
	{
		tok_l = tok_l->next;
		if (*(char *)tok_l->content == PIPE)
			clean_exit(input, "syntax error near unexpected token `|'");
		tok_l = tmp;
	}
}

void	lexer(t_input *input, t_list *tok_l)
{
	char	sign;

	while (tok_l)
	{
		sign = *(char *)tok_l->content;
		if (is_meta(sign))
			check_syntax_error(input, tok_l, sign);
		tok_l = tok_l->next;
	}
}