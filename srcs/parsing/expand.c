/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/22 16:57:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_identifier(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static int	is_first_identifier(int c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

static t_list	*search_token(char *str, size_t len, t_list *env)
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

static char	*get_expand_value(char *str, size_t len, t_sh *sh)
{
	t_list	*l;
	char	*res;

	if (*str == '?')
		res = ft_itoa(sh->last_exit_code);
	else
	{
		l = search_token(str, len, sh->env);
		if (l)
			res = ft_strdup(ft_strchr((char *)l->content, '=') + 1);
		else
			res = ft_strdup("\0");
	}
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

static char	*expanded_content(char *s, t_sh *sh)
{
	char	*start;
	char	*buf;
	char	*token_val;

	buf = NULL;
	while (*s)
	{
		start = s;
		while (*s && *s != '$')
			s++;
		buf = ft_strnextend(buf, start, s - start);
		if (*s == '$')
		{ 
			s++;
			if (*s == '?')
				token_val = get_expand_value()
		}
		token_val = get_expand_value(s, s - start, sh);

	}
}

static void	expand_content(t_list *token, char *tok_str, t_sh *sh)
{
	char	*tmp;

	tmp = token->content;
	token->content = expanded_content(tok_str, sh);
	free(tmp);
}

static void	expand_remove_quotes(t_list *token, char *tok_str, t_sh *sh)
{
	char	*tmp;

	if (*tok_str == '$')
		tok_str++;
	if (*tok_str && *tok_str == DB_QUOTE)
		expand_content(token, tok_str, sh);
	tmp = token->content;
	token->content = ft_substr(tmp, 1, ft_strlen(tmp) - (2));
	free(tmp);
}

void	token_expand(t_list *token, t_sh *sh)
{
	char	*tok_str;
	char	*tmp;

	tmp = NULL;
	while (token)
	{
		if (token->type == HEREDOC && token->next && token->next->next)
			token = token->next->next;
		tok_str = (char *)token->content;
		if (is_quote(token->type) || is_dollar_quote(token))
			expand_remove_quotes(token, tok_str, sh);
		else if (token->type == WORD && ft_strlen(tok_str) > 1)
			expand_content(token, tok_str, sh);
 		token = token->next;
	}
}
