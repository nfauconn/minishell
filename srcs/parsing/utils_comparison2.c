/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_comparison2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:56:44 by user42            #+#    #+#             */
/*   Updated: 2022/06/26 23:00:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar_quote(t_list *token)
{
	char	*tok;

	tok = (char *)token->content;
	if (*tok == '$' && ft_strlen(tok) > 1 && is_quote(*(tok + 1)))
		return (1);
	return (0);
}

int	is_word(int c)
{
	return (!is_quote(c) && !is_redir(c) && !is_blank(c) && !is_sep(c));
}
