/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:10:00 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/08 15:26:48 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_double(char *s, int c)
{
	s++;
	if (*s && *s == c)
		s++;
	if (*s && *s == '\0')
		return (1);
	return (0);
}

void	get_parsing_types(t_list *token)
{
	char	*tmp;

	while (token)
	{
		tmp = (char *)token->content;
		token->type = *tmp;
		if (token->type == IN_REDIR)
		{
			if (check_double(tmp, *tmp))
				token->type = HEREDOC;
		}
		else if (token->type == OUT_REDIR)
		{
			if (check_double(tmp, *tmp))
				token->type = APPEND_REDIR;
		}
		else if (token->type == '$')
		{
			tmp++;
			if (*tmp == '\0')
				token->type = WORD;
			else
				token->type = TO_EXPAND;
		}
		else if (token->type != PIPE && !is_quote(token->type))
			token->type = WORD;
		token = token->next;
	}
}
