/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_try.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/22 20:14:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_realloc(char *alloc_str, char *str, size_t len)
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
	t_list	*l;
	char	*res;

	l = search_token(str, len, env);
	if (l)
		res = ft_strdup(ft_strchr((char *)l->content, '=') + 1);
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

static void	replace_and_free(void **prev_content, void *new_content)
{
	void	*tmp;

	tmp = *prev_content;
	*prev_content = new_content;
	free(tmp);
}

static void	expand_remove_quotes(t_list *token, char *tok_str, t_sh *sh)
{
	char	*buf;
	char	*start;
	char	*token_val;

	if (*tok_str == '$')
		tok_str++;
	if (*tok_str && *tok_str == DB_QUOTE)
	{
		token_val = NULL;
		while (*tok_str)
		{
			start = tok_str;
			while (*tok_str && *tok_str != '$')
				tok_str++;
			buf = ft_realloc(buf, start, tok_str - start);
			if (*tok_str == '$')
			{
				token_val = expanded_content(&tok_str, sh);
				buf = ft_realloc(buf, token_val, ft_strlen(token_val));
				free(token_val);
				tok_str++;
			}
		}
		replace_and_free(&token->content, buf);
	}
	buf = token->content;
	replace_and_free(&token->content, ft_substr(buf, 1, ft_strlen(buf) - (2)));
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
		else if (token->type == '$' && ft_strlen(tok_str) > 1)
			replace_and_free(&token->content, expanded_content(tok_str, sh));
 		token = token->next;
	}
}
