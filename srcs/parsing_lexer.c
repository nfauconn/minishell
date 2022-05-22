/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/05/22 17:56:58 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	check_syntax_error(char	*token, char sign)
{
	if (sign == PIPE && *(token + 1) == PIPE)
	{
		ft_printerror("minish: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (is_meta(sign) && ft_strlen(token) > 2)
	{
		ft_printerror("minish: syntax error near unexpected token `%c'\n", sign);
		return (1);
	}
	return (0);
}

int	lexer(t_list *tok_l)
{
	char	sign;

	while (tok_l)
	{
		sign = *(char *)tok_l->content;
		if (is_meta(sign))
			if (check_syntax_error((char *)tok_l->content, sign))
				return (1);
		tok_l = tok_l->next;
	}
	return (0);
}
