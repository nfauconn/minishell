/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:09:58 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/21 16:43:49 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_types_for_lex(t_list *token)
{
	char	*tmp;

	while (token)
	{
		tmp = (char *)token->content;
		token->type = *tmp;
		if (token->type == IN_REDIR)
		{
			if (!ft_strcmp(tmp, "<<"))
				token->type = HEREDOC;
		}
		else if (token->type == OUT_REDIR)
		{
			if (!ft_strcmp(tmp, ">>"))
				token->type = APPEND_REDIR;
		}
		else if (!is_sep(token->type) && !is_quote(token->type)
			&& !is_blank(token->type))
			token->type = WORD;
		token = token->next;
	}
}

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

void	set_types_complete(t_list *token)
{
	while (token)
	{
		if (token->type == IN_REDIR)
			token = set_next_type(token, INFILE_PATH);
		else if (token->type == HEREDOC)
			token = set_next_type(token, DELIMITER);
		else if (token->type == OUT_REDIR)
			token = set_next_type(token, TRUNC_OUTFILE_PATH);
		else if (token->type == APPEND_REDIR)
			token = set_next_type(token, APPEND_OUTFILE_PATH);
		else if (is_quote(token->type))
			token->type = WORD;
		token = token->next;
	}
}
