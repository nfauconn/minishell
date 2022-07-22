/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:41:54 by user42            #+#    #+#             */
/*   Updated: 2022/07/22 20:47:13 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_last_status(t_sh *sh)
{
	char	*tmp;

	if (!sh->last_status_str)
		sh->last_status_str = ft_itoa(sh->last_status);
	else
	{
		tmp = sh->last_status_str;
		sh->last_status_str = ft_itoa(sh->last_status);
		free(tmp);
	}
	return (sh->last_status_str);
}

t_list	*set_delim_type(t_list *token)
{
	t_list	*start;

	start = token;
	token = token->next;
	while (token && !is_metacharacter(token->type))
	{
		if (ft_strchr((char *)token->content, QUOTE))
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
