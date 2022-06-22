/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/22 13:49:28 by mdankou          ###   ########.fr       */
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

static char	*get_expand_value(char *str, size_t start, size_t len, t_list *env)
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

static char	*ft_strnextend(char *alloc_str, char *str, size_t len)
{
	size_t	old_len;
	char	*new;

	if (str == NULL)
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

static char	*var_expand(char *token, t_list *env)
{
	char	*start;
	char	*res;
	char	*token_val;

	res = NULL;
	while (*token)
	{
		start = token;
		while (*token && *token != '$')
			token++;
		res = ft_strnextend(res, start, token - start);
		if (*token == '$' && is_identifier(*(token + 1)))
		{
			token++;
			start = token;
			while (is_identifier(*token))
				token++;
			if (isalpha(*start) || *start == '_')
				token_val = get_expand_value(start, 0, token - start, env);
			else
				token_val = ft_strdup(start + 1);
			res = ft_strnextend(res, token_val, ft_strlen(token_val));
			free(token_val);
		}
		else if (*token == '$' && !is_identifier(*(token + 1)))
		{
			res = ft_strnextend(res, token, 1);
			token++;
		}
	}
	return (res);
}

void	token_expand(t_list *token, t_list *env)
{
	int	start;
	char	*tok;
	char	*tmp;

	tmp = NULL;
	while (token)
	{
		tok = (char *)token->content;
		if (token->type == HEREDOC && token->next->next)
		{
			token = token->next->next;
			continue ;
		}
		start = 1;
		if (*tok == '$' && ft_strlen(tok) > 1 && is_quote(*(++tok)))
			start++;
		if (*tok == QUOTE || *tok == DB_QUOTE)
		{
			if (*tok == DB_QUOTE)
			{
				tmp = token->content;
				token->content = var_expand(tok, env);
				free(tmp);
			}
			tmp = token->content;
			token->content = ft_substr(tmp, 1, ft_strlen(tmp) - (2));
			free(tmp);
		}
		else if (token->type == WORD)
		{
			tmp = token->content;
			token->content = var_expand(tmp, env);
			free(tmp);
		}
 		token = token->next;
	}
}
