/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tryy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/23 19:59:37 by user42           ###   ########.fr       */
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

static void	expand_string(char *str, char *ptr, t_sh *sh)
{
	char	*buf;
	char	*token_val;
	char	*start;

	buf = NULL;
	token_val = NULL;
	while (*ptr)
	{
		start = ptr;
		while (*ptr && *ptr != '$')
			ptr++;
		insert_into_buffer(buf, start, ptr - start);
		token_val = expanded_content(ptr, sh);
		insert_into_buffer(buf, token_val, ft_strlen(token_val));
		free(token_val);
	}
	free(str);
	str = buf;
}

static char	*expand_quotes(char *str, char *ptr, t_sh *sh)
{
	char	*start;
	char	*buf;
	char	*tmp;

	buf = NULL;
	if (*ptr == '$')
		ptr++;
	if (*ptr && *ptr == DB_QUOTE)
		expand_string(str, ptr, sh);
	start = ptr + 1;
	while (*ptr)
		ptr++;
	insert_into_buffer(buf, start, ptr - start - 1);
	free(tmp);
	return (buf);
}

void	token_expand(t_list *token, t_sh *sh)
{
	char	*ptr;
	char	*tmp;

	tmp = NULL;
	while (token)
	{
		if (token->type == DELIMITER)
			token = token->next;
		ptr = (char *)token->content;
		if (is_quote(*ptr) || is_dollar_quote(token))
		{
			tmp = token->content;
			token->content = expand_quotes(ptr, sh);
			free(tmp);
		}
		else if (ft_strchr(ptr, '$') && ft_strlen(ptr) > 1)
		{
			tmp = token->content;
			token->content = expand_string(ptr, sh);
			free(tmp);
		}
		token = token->next;
	}
}
