/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:28:00 by user42            #+#    #+#             */
/*   Updated: 2022/06/24 10:40:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*search_var(char *str, size_t len, t_list *env)
{
	while (env)
	{
		if (!ft_strncmp(str, (char *)env->content, len)
			&& ((char *)env->content)[len] == '=')
			break ;
		env = env->next;
	}
	return (env);
}

static char	*get_expand_value(char *str, size_t len, t_list *env)
{
	t_list	*var_line;
	char	*res;

	var_line = search_var(str, len, env);
	if (var_line)
		res = ft_strdup(ft_strchr((char *)var_line->content, '=') + 1);
	else
		res = ft_strdup("\0");
	return (res);
}

static char	*expanded_content(char **s, t_sh *sh)
{
	char	*start;
	char	*token_val;

	(*s)++;
	start = *s;
	if (*start == '?')
		token_val = ft_itoa(sh->last_exit_code);
	else if (is_identifier(*start) && !ft_isdigit(*start))
	{
		while (is_identifier(**s))
			(*s)++;
		token_val = get_expand_value(start, (*s) - start, sh->env);
	}
	else
	{
		(*s)++;
		token_val = ft_strdup("");
	}
	return (token_val);
}

void	add_expanded_var(char **buf, char **ptr, t_sh *sh)
{
	char	*token_val;

	if (**ptr == '$')
	{
		token_val = expanded_content(ptr, sh);
		ft_replace_free_old((void **)buf, (void *)ft_strjoin(*buf, *ptr));
		free(token_val);
	}
}

char	*alloc_until_var(char *buf, char **ptr, char *start)
{
	char	*new;

	new = NULL;
	while (**ptr && **ptr != '$')
		(*ptr)++;
	new = expand_and_add(buf, start, (*ptr) - start);
	return (new);
}
