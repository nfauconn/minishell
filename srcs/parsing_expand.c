/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/01 18:21:45 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_identifier(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static t_list	*search_token(char *str, size_t start, size_t len, t_list *env)
{
	while (env)
	{
		if (!ft_strncmp(str + start, (char *)env->content, len)
			&& ((char *)env->content)[len] == '=')
			break ;
		env = env->next;
	}
	return (env);
}

static char	*get_token_value(char *str, size_t start, size_t len, t_list *env)
{
	t_list	*l;
	char	*res;

	l = search_token(str, start, len, env);
	if (l)
		res = ft_strdup(ft_strchr((char *)l->content, '=') + 1);
	else
		res = ft_strdup("");
	return (res);
}

static char	*ft_strnextend(char *alloc_str, char *str, size_t len)
{
	size_t	old_len;
	char	*new;

	if (str == NULL || len == 0)
		return (alloc_str);
	if (alloc_str != NULL)
		old_len = ft_strlen(alloc_str);
	else
		old_len = 0;
	new = (char *)malloc(sizeof(char) * (len + old_len + 1));
	if (!new)
	{
		free(alloc_str);
		return (NULL);
	}
	if (old_len)
		ft_strlcpy(new, alloc_str, old_len + 1);
	ft_strlcpy(new + old_len, str, len + 1);
	free(alloc_str);
	return (new);
} 

static char	*do_expand(char *token, t_list *env)
{
	ssize_t	i;
	char	*res;
	char	*token_val;

	res = NULL;
	i = 0;
	while (token[i])
	{
		while (token[i] && token[i] != '$')
			i++;
		res = ft_strnextend(res, token, i);
		if (token[i] == '$')
		{
			token += i + 1;
			i = 0;
			while (is_identifier(token[i]))
				i++;
			if (i == 0)
				res = ft_strnextend(res, token - 1, 1);
			else
			{
				token_val = get_token_value(token, 0, i, env);
				res = ft_strnextend(res, token_val, ft_strlen(token_val));
			}
		}
	}
	return (res);
}

void	var_expand(t_list *token_list, t_list *env)
{
	int	i = 1;
	int	start;
	char	*tok;
	char	*tmp;

	tmp = NULL;
	while (token_list)
	{
		start = 0;
		tok = (char *)token_list->content;
		if (!ft_strcmp(tok, "<<"))
		{
			token_list = token_list->next;
			if (!ft_strcmp(token_list->content, " "))
				token_list = token_list->next;
		}
		if (*tok == '$' && is_quote(*(tok + 1)))
		{
			tok++;
		}
/* 		if (*tok == DB_QUOTE)
		{
			tok++;
			printf("tok n%d has double quotes!\n", i);
			if $ in string
					expand tok
			cut out quotes
		} */
		else if (*tok == QUOTE)
		{
			tok++;
			tmp = token_list->content;
			token_list->content = ft_substr(tok, 0, ft_strlen(tok) - 1);
			free(tmp);
		}
		else
		{
			tmp = token_list->content;
			token_list->content = do_expand(tmp, env);
		}
 		token_list = token_list->next;
		i++;
	}
}
