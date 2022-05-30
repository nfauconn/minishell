/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:36:22 by user42            #+#    #+#             */
/*   Updated: 2022/05/30 13:46:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	lexer(t_list *tok_l)
{
	char	sign;

	while (tok_l)
	{
		sign = *(char *)tok_l->content;
		if (is_separator(sign) && ft_strlen((char *)tok_l->content) > 2)
		{
			ft_printerror("minish: syntax error near unexpected token `%c'\n", sign);
			return (FAILURE);
		}
		tok_l = tok_l->next;
	}
	return (SUCCESS);
}
