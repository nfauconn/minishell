/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/05/18 12:45:34 by user42           ###   ########.fr       */
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
		if (sign == IN_REDIR || sign == OUT_REDIR || sign == PIPE)
			check_syntax_error(input, tok_l, sign);
		tok_l = tok_l->next;
	}
}
