/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:09:58 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/26 22:32:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (token->type == IN_REDIR && !ft_strcmp(tmp, "<<"))
		{
			token->type = HEREDOC;
			token = set_next_type(token, DELIMITER);
		}
		else if (token->type == OUT_REDIR &&!ft_strcmp(tmp, ">>"))
			token->type = APPEND_REDIR;
		else if (!is_sep(token->type) && !is_quote(token->type)
			&& !is_blank(token->type))
			token->type = WORD;
		token = token->next;
	}
}

void	complete_types(t_list *token)
{
	while (token)
	{
		if (is_quote(token->type))
			token->type = WORD;
		if (token->type == IN_REDIR)
			token = set_next_type(token, INFILE_PATH);
		else if (token->type == HEREDOC)
			token = set_next_type(token, DELIMITER);
		else if (token->type == OUT_REDIR)
			token = set_next_type(token, TRUNC_OUTFILE_PATH);
		else if (token->type == APPEND_REDIR)
			token = set_next_type(token, APPEND_OUTFILE_PATH);
		token = token->next;
	}
}
