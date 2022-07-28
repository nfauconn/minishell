/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:41:54 by user42            #+#    #+#             */
/*   Updated: 2022/07/28 20:21:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*set_delim_type(t_list *token)
{
	t_list	*start;

	start = token;
	token = token->next;
	while (token && !is_metacharacter(token->type))
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
	while (env)
	{
		if (!ft_strncmp(str, (char *)env->content, len)
			&& ((char *)env->content)[len] == '=')
			return (ft_strchr((char *)env->content, '=') + 1);
		env = env->next;
	}
	return (NULL);
}
