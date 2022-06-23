/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/23 17:50:34 by user42           ###   ########.fr       */
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

void	add_expanded_var(char **buf, char **tok_str, t_sh *sh)
{
	char	*token_val;

	if (**tok_str == '$')
	{
		token_val = expanded_content(tok_str, sh);
		ft_replace_free_old((void **)buf, (void *)ft_strjoin(*buf, *tok_str));
		free(token_val);
	}
}

char	*alloc_until_var(char *buf, char **tok_str, char *start)
{
	char	*new;

	new = NULL;
	while (**tok_str && **tok_str != '$')
		(*tok_str)++;
	new = ft_realloc_and_add(buf, start, (*tok_str) - start);
	return (new);
}

static char	*expand_string(char *tok_str, t_sh *sh)
{
	char	*buf;
	char	*token_val;
	char	*start;

	buf = NULL;
	token_val = NULL;
	while (*tok_str)
	{
		start = tok_str;
		buf = alloc_until_var(buf, &tok_str, start);
		add_expanded_var(&buf, &tok_str, sh);
	}
	return (buf);
}

static char	*expand_quotes(char *tok_str, t_sh *sh)
{
	char	*buf;
	char	*tmp;

	buf = NULL;
	if (*tok_str == '$')
		tok_str++;
	if (*tok_str && *tok_str == QUOTE)
	{
		buf = ft_substr(tok_str, 1, ft_strlen(tok_str) - 2);
	}
	else if (*tok_str && *tok_str == DB_QUOTE)
	{
		buf = expand_string(tok_str, sh);
		tmp = buf;
		buf = ft_substr(buf, 1, ft_strlen(buf) - 2);
		free(tmp);
	}
	return (buf);
}

void	token_expand(t_list *token, t_sh *sh)
{
	char	*tok_str;
	char	*tmp;

	tmp = NULL;
	while (token)
	{
		if (token->type == DELIMITER)
			token = token->next;
		tok_str = (char *)token->content;
		if (is_quote(*tok_str) || is_dollar_quote(token))
		{
			tmp = token->content;
			token->content = expand_quotes(tok_str, sh);
			free(tmp);
		}
		else if (ft_strchr(tok_str, '$') && ft_strlen(tok_str) > 1)
		{
			tmp = token->content;
			token->content = expand_string(tok_str, sh);
			free(tmp);
		}
		token = token->next;
	}
}
