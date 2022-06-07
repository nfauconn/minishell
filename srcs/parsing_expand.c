/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/07 12:49:37 by nfauconn         ###   ########.fr       */
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

static char	*var_expand(char *token, t_list *env)
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

void	cmd_list_expand(t_list *token, t_list *env)
{
	int	start;
	char	*tok;
	char	*tmp;

	tmp = NULL;
	while (token)
	{
		start = 0;
		tok = (char *)token->content;
		if (ft_strcmp(tok, "<<")  == 0)
		{
			token = token->next;
			if (!ft_strcmp(token->content, " "))
				token = token->next;
			tmp = (char *)token->content;
			if (is_quote(*tmp))
			{
				// specific case --> delimiter will be without quotes +++++ heredoc strings will not be expanded
			}
			if (token->next)
			{
				token = token->next;
				tok = (char *)token->content;
			}
			else
				break ;
		}
		if (*tok == '$' && is_quote(*(tok + 1)))
		{
			tok++;
		}
 		if (*tok == DB_QUOTE)
		{
			tmp = token->content;
			token->content = do_expand(tok, env);
			free(tmp);
			tok = token->content;
		}
		if (is_quote(*tok))
		{
			tmp = token->content;
			token->content = ft_substr(tok, 1, ft_strlen(tok) - 2);
			free(tmp);
		}
		else
		{
			tmp = token->content;
			token->content = do_expand(tmp, env);
			free(tmp);
		}
 		token = token->next;
	}
}
