/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:10:00 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/07 19:41:50 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_parsing_types(t_list *token)
{
	char	*tmp;

	while (token)
	{
		tmp = (char *)token->content;
		token->type = *tmp;
		if (token->type == '<')
		{
			tmp++;
			if (*tmp && *tmp == '<')
			{
				tmp++;
				if (*tmp == '\0')
					token->type = HEREDOC;
			}
		}
		if (token->type == '>')
		{
			tmp++;
			if (*tmp && *tmp == '>')
			{
				tmp++;
				if (*tmp == '\0')
					token->type = APPEND_REDIR;
			}
		}
		if (token->type == '$')
		{
			tmp++;
			if (*tmp == '\0')
				token->type = WORD;
			else
				token->type = TO_EXPAND;
		}
		token = token->next;	
	}
}
