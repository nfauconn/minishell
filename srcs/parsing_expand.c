/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/25 18:29:08 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
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
		res = ft_strdup("\0");
	return (res);
}

static char	*ft_strnextend(char *alloc_str, char *str, size_t n)
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

static char	*do_expand(char *token, t_list *env)
{
	size_t	i;
	ssize_t	len;
	char	*res;
	char	*token_val;

	res = NULL;
	i = (token[0] == '\"' || token[0] == '\'');
	while (token[i] && token[i] != '\"')
	{
			printf("token = %s\n", token);

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
			printf("BLABLA len = %zd\n", len);
			res = ft_strnextend(res, token + i, len);
		}
		i += len;
	}
	return (res);
}

static char	*token_expand(char *token, t_list *env)
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
} */

void	var_expand(t_list **token_list, t_list *env)
{
	int	i = 0;
	t_list	**head;
	char	*tok;

	(void)env;
	head = token_list;
	while (*token_list)
	{
		tok = (char *)(*token_list)->content;
		if (*tok == '$')
		{
			printf("tok n%d has a $!\n", i);
			/* expand tok */
		}
		else if (*tok == DB_QUOTE)
		{
			tok++;
			if (*tok && tok[ft_strlen(tok) - 1] == DB_QUOTE)
				printf("tok n%d has double quotes!\n", i);
			/* if $ in string */
					/* expand tok */
			/* cut out quotes */
		}
		else if (*tok == QUOTE)
		{
			tok++;
			if (*tok && tok[ft_strlen(tok) - 1] == QUOTE)
				printf("tok n%d has simple quotes!\n", i);
			/* cut out quotes */
		}
		(*token_list) = (*token_list)->next;
		i++;
	}
	token_list = head;
}
