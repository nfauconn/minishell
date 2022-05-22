/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:27:49 by mdankou           #+#    #+#             */
/*   Updated: 2022/05/22 18:13:17 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*search_token(char *str, size_t start, size_t len, t_list *env)
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

char	*get_token_value(char *str, size_t start, size_t len, t_list *env)
{
	t_list	*l;
	char	*res;

	l = search_token(str, start, len, env);
	if (l)
		res = ft_strdup(ft_strchr((char *)l->content, '=') + 1);
	else
		res = ft_strdup("\0");
	return (res);
}

char	*ft_strnextend(char *alloc_str, char *str, size_t n)
{
	size_t	len;
	size_t	old_len;
	char	*new;

	if (str == NULL)
		return (alloc_str);
	len = ft_strlen(str);
	if (n == 0 || len == 0)
		return (alloc_str);
	if (len > n)
		len = n;
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

char	*do_expand(char *token, t_list *env)
{
	size_t	i;
	ssize_t	len;
	char	*res;
	char	*token_val;

	res = NULL;
	i = (token[0] == '\"' || token[0] == '\'');
	while (token[i] && token[i] != '\"')
	{
		len = ft_strchr(token + i, '$') - (token + i);
		if (len >= 0)
		{
			res = ft_strnextend(res, token + i, len);
			i += len + 1;
			len = 0;
			while (token[i + len] && token[i + len] != '\"'
				&& (ft_isalnum(token[i + len]) || token[i + len] == '_'))
				++len;
			if (len == 0)
				res = ft_strnextend(res, token + i + ++len, 1);
			else
			{
				token_val = get_token_value(token, i, len, env);
				res = ft_strnextend(res, token_val, ft_strlen(token_val));
			}
		}
		else
		{
			len = ft_strlen(token + i) - 1;
			res = ft_strnextend(res, token + i, len);
		}
		i += len;
	}
	return (res);
}

char	*var_expand(char *token, t_list *env)
{
	char	*str;

	if (token[0] == token[ft_strlen(token) - 1] && token[0] == '\'')
	{
		str = (char *)malloc(sizeof(char) * ft_strlen(token) - 1);
		if (!str)
			return (NULL);
		ft_strlcpy(str, token + 1, ft_strlen(token) - 1);
		return (str);
	}
	return (do_expand(token, env));
}
