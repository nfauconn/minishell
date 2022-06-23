/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/23 15:34:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_identifier(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static t_list	*search_token(char *str, size_t len, t_list *env)
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

	var_line = search_token(str, len, env);
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

static void	add_expanded_var(char **buf, char **tok_str, t_sh *sh)
{
	char	*token_val;

	if (**tok_str == '$')
	{
		token_val = expanded_content(tok_str, sh);
		*buf = ft_replace_free_old(buf, ft_strjoin(*buf, *tok_str));
		free(token_val);
	}
}

static void	alloc_until_var(char **buf, char **tok_str, char *start)
{
	while (**tok_str && **tok_str != '$')
		(*tok_str)++;
	*buf = ft_realloc(*buf, start, (*tok_str) - start);
}

static void	expand_remove_quotes(t_list *token, char *tok_str, t_sh *sh)
{
	char	*buf;
	char	*start;
	char	*token_val;

	if (*tok_str == '$')
		tok_str++;
	if (*tok_str && *tok_str == QUOTE)
	{
		buf = ft_strdup(tok_str);
	}
	else if (*tok_str && *tok_str == DB_QUOTE)
	{
		token_val = NULL;
		while (*tok_str)
		{
			start = tok_str;
			alloc_until_var(&buf, &tok_str, start);
			add_expanded_var(&buf, &tok_str, sh);
		}
		ft_replace_free_old(&token->content, buf);
	}
	ft_replace_free_old(&token->content, ft_substr(buf, 1, ft_strlen(buf) - (2)));
}

void	token_expand(t_list *token, t_sh *sh)
{
	char	*tok_str;
	char	*tmp;

	tmp = NULL;
	while (token)
	{
		tok_str = (char *)token->content;
		if (token->type == HEREDOC)
		{
			token = skip_token(token, BLANK);
			token = skip_token(token, WORD);
			continue ;
		}
		if (is_quote(token->type) || is_dollar_quote(token))
			expand_remove_quotes(token, tok_str, sh);
		else if (token->type == '$' && ft_strlen(tok_str) > 1)
			ft_replace_free_old(&token->content, expanded_content(&tok_str, sh));
 		token = token->next;
	}
}
