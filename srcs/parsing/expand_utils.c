/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:41:54 by user42            #+#    #+#             */
/*   Updated: 2022/07/31 21:31:39 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*set_delim_type(t_list *token)
{
	t_list	*start;

	start = token;
	token = token->next;
	while (token && !is_metacharacter(*(char *)token->content))
	{
		if (ft_strchr((char *)token->content, QUOTE)
			|| ft_strchr((char *)token->content, DB_QUOTE))
		{
			token = start;
			break ;
		}
		token->type = HEREDOC_DELIM;
		token = token->next;
	}
	if (token == start && token->next)
		token = set_next_words_type(token, QUOTED_HEREDOC_DELIM);
	return (start->next);
}

char	*var_value(char *str, size_t len, t_list *env)
{
	char	*env_line;

	while (env)
	{
		env_line = (char *)env->content;
		if (!ft_strncmp(str, env_line, len) && (env_line)[len] == '=')
			return (ft_strdup(ft_strchr(env_line, '=') + 1));
		env = env->next;
	}
	return (NULL);
}
