/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:09:58 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/23 00:17:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*set_next_words_type(t_list *token, int type)
{
	token = token->next;
	while (token && !is_metacharacter(token->type))
	{
		token->type = type;
		token = token->next;
	}
	return (token);
}

static t_list	*set_type(t_list *token, char *tmp)
{
	if (token->type == '<' && !ft_strcmp(tmp, "<"))
		token = set_next_words_type(token, INFILE_NAME);
	else if (token->type == '<' && !ft_strcmp(tmp, "<<")
		&& token->next->type != QUOTED_HEREDOC_DELIM)
		token = set_next_words_type(token, HEREDOC_DELIM);
	else if (token->type == '<' && !ft_strcmp(tmp, "<<")
		&& token->next->type == QUOTED_HEREDOC_DELIM)
		token = set_next_words_type(token, QUOTED_HEREDOC_DELIM);
	else if (token->type == '>' && !ft_strcmp(tmp, ">"))
		token = set_next_words_type(token, OUTFILE_NAME);
	else if (token->type == '>' && !ft_strcmp(tmp, ">>"))
		token = set_next_words_type(token, APPEND_OUTFILE_NAME);
	else if (!is_metacharacter(token->type))
	{
		token->type = WORD;
		token = set_next_words_type(token, WORD);
	}
	return (token);
}

void	set_token_types(t_list *token)
{
	char	*tmp;

	while (token)
	{
		tmp = (char *)token->content;
		token->type = *tmp;
		token = set_type(token, tmp);
		if (token)
			token = token->next;
	}
}
