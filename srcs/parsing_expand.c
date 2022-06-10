/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/10 14:09:14 by nfauconn         ###   ########.fr       */
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
			token_val = get_expand_value(start, 0, token - start, env);
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
		start = 0;
		tok = (char *)token->content;
		if (token->type == HEREDOC)
		{
			token = token->next;
			if (token->next)
				token = token->next;
		}
		if (token->type == QUOTE || token->type == DB_QUOTE)
		{
			if (token->type == DB_QUOTE)
			{
				tmp = token->content;
				token->content = var_expand(tok, env);
				free(tmp);
			}
			tmp = token->content;
			token->content = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
			free(tmp);
		}
		else if (token->type == TO_EXPAND)
		{
			tmp = token->content;
			token->content = var_expand(tmp, env);
			free(tmp);
		}
 		token = token->next;
	}
/* 	char	*tok;
	char	*tmp;
	char	*ret;

	ret = NULL;
	tmp = NULL;
	tok = (char *)token->content;
	if (token->type == QUOTE || token->type == DB_QUOTE)
	{
		if (token->type == DB_QUOTE)
			ret = var_expand((char *)token->content, env);
		tmp = ret;
		ret = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
		free(tmp);
	}
	else if (token->type == TO_EXPAND)
		ret = var_expand(token->content, env);
	return (ret); */
}
