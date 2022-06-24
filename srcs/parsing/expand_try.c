/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_try.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/24 12:12:04 by user42           ###   ########.fr       */
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

	token_val = NULL;
	if (**s)
		(*s)++;
	start = *s;
	if (*start && *start == '?')
		token_val = ft_itoa(sh->last_exit_code);
	else if (*start && is_identifier(*start) && !ft_isdigit(*start))
	{
		while (is_identifier(**s))
			(*s)++;
		token_val = get_expand_value(start, (*s) - start, sh->env);
	}
	else if (*start)
	{
		(*s)++;
		token_val = ft_strdup("");
	}
	return (token_val);
}

static void	expand_string(char **to_expand, char *ptr, t_sh *sh)
{
	char	*token_val;
	char	*start;
	char	*tmp;

	new = NULL;
	token_val = NULL;
	while (*ptr)
	{
		start = ptr;
		while (*ptr && *ptr != '$')
			ptr++;
		ft_strljoin_free(new, start, ptr - start);
		token_val = expanded_content(&ptr, sh);
		if (token_val)
		{
			if (*token_val)
				ft_strljoin_free(new, token_val, ft_strlen(token_val));
			free(token_val);
		}
	}
	if (*to_expand)
	{
		tmp = *to_expand;
		*to_expand = new;
		free(tmp);
	}
	else
		*to_expand = new;
}

static void	expand_quotes(char **to_expand, char *ptr, t_sh *sh)
{
	t_bool	quote;
	char	*start;
	void	*new;
	char	*tmp;

	quote = 1;
	new = NULL;
	if (*ptr && *ptr == '$')
		ptr++;
	if (*ptr && is_quote(*ptr) && ft_strlen(ptr) == quote + quote)
	{
		tmp = *to_expand;
		*to_expand = ft_strdup("");
		free(tmp);
		return ;
	}
	if (*ptr && *ptr == DB_QUOTE)
		expand_string(to_expand, ptr, sh);
	start = ptr + quote;
	while (*ptr)
		ptr++;
	ft_strljoin_free(new, start, ptr - start - quote);
	tmp = *to_expand;
	*to_expand = new;
	free(tmp);
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
			expand_quotes((char **)token->content, ptr, sh);
		}
		else if (ft_strchr(ptr, '$') && ft_strlen(ptr) > 1)
		{
			expand_string((char **)token->content, ptr, sh);
		}
		token = token->next;
	}
}
