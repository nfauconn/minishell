/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:09:58 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/31 21:05:58 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*set_next_words_type(t_list *token, int type)
{
	token = token->next;
	if (token)
	{
		token->type = *(char *)token->content;
		while (token && !is_metacharacter(token->type))
		{
			token->type = type;
			token = token->next;
			if (token)
				token->type = *(char *)token->content;
		}
	}
	return (token);
}

static t_list	*set_type(t_list *token, char *tok_content)
{
	if (*tok_content == '<' && !ft_strcmp(tok_content, "<"))
		token = set_next_words_type(token, INFILE_NAME);
	else if (*tok_content == '<' && !ft_strcmp(tok_content, "<<"))
	{
		token = token->next;
		token->type = *(char *)token->content;
		if (token->type == QUOTED_HEREDOC_DELIM)
			token = set_next_words_type(token, QUOTED_HEREDOC_DELIM);
		else
			token = set_next_words_type(token, HEREDOC_DELIM);
	}
	else if (*tok_content == '>' && !ft_strcmp(tok_content, ">"))
		token = set_next_words_type(token, OUTFILE_NAME);
	else if (*tok_content == '>' && !ft_strcmp(tok_content, ">>"))
		token = set_next_words_type(token, APPEND_OUTFILE_NAME);
	else if (!is_metacharacter(*tok_content))
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
		if (!is_quote(*tmp))
			token->type = *tmp;
		token = set_type(token, tmp);
		if (token)
			token = token->next;
	}
}
