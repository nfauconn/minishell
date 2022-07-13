/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:09:58 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/13 15:19:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_list	*set_next_type(t_list *token, int type)
{
	if (token->next)
	{
		token->next->type = type;
		return (token->next);
	}
	else
		return (token);
}

void	set_types_for_lex(t_list *token)
{
	char	*tmp;

	while (token)
	{
		tmp = (char *)token->content;
		token->type = *tmp;
 		if (token->type == '<' && !ft_strcmp(tmp, "<<"))
		{
			token->type = HEREDOC;
			token = set_next_type(token, DELIMITER);
		}
		else if (token->type == '>' && !ft_strcmp(tmp, ">>"))
		{
			token->type = APPEND;
		}
		if (!is_sep(token->type) && !is_quote(token->type)
			&& !is_blank(token->type) && !is_redir(token->type)
			&& token->type != DELIMITER)
			token->type = WORD;
		token = token->next;
	}
}

void	complete_types(t_list *token)
{
	while (token)
	{
		if (token->type == '<' && token->type != HEREDOC)
			token = set_next_type(token, INFILE);
		else if (token->type == '>' && token->type != APPEND)
			token = set_next_type(token, TRUNC);
		else if (token->type == APPEND)
			token = set_next_type(token, APPEND_FILE);
		token = token->next;
	}
}
