/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:13:37 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/22 20:47:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*expanded_content(char **s, t_sh *sh)
{
	char	*start;

	(*s)++;
	start = *s;
	if (*start)
	{
		if (*start == '?')
		{
			(*s)++;
			return (get_last_status(sh));
		}
		else if (is_identifier(*start) && !ft_isdigit(*start))
		{
			while (is_identifier(**s))
				(*s)++;
			return (var_value(start, (*s) - start, sh->env));
		}
		else
			(*s)++;
	}
	return (NULL);
}

char	*expand_string(char *ptr, t_sh *sh)
{
	char	*var_val;
	char	*new;
	size_t	new_size;
	char	*start;

	var_val = NULL;
	new = NULL;
	new_size = 0;
	while (*ptr)
	{
		if (*ptr == '$')
		{
			var_val = expanded_content(&ptr, sh);
			new_size = ft_strlen(new) + ft_strlen(var_val) + 1;
			new = ft_realloc(new, new_size);
			ft_strlcat(new, var_val, new_size);
		}
		start = ptr;
		while (*ptr && *ptr != '$')
			ptr++;
		new_size += ptr - start;
		new = ft_realloc(new, new_size);
		ft_strlcat(new, start, new_size);
	}
	return (new);
}

static char	*expand_quotes(char *ptr, t_sh *sh)
{
	t_bool	quote;
	char	*start;
	char	*new;
	char	*tmp;

	quote = 1;
	new = NULL;
	if (*ptr == '$')
		ptr++;
	start = ptr + quote;
	if (ft_strlen(ptr) == quote + quote)
		new = ft_strdup("");
	else if (*ptr == QUOTE)
		new = ft_substr(start, 0, ft_strlen(start) - quote);
	else if (*ptr == DB_QUOTE)
	{
		tmp = expand_string(start, sh);
		new = ft_substr(tmp, 0, ft_strlen(tmp));
		free(tmp);
	}
	return (new);
}

void	token_expand(t_list *token, t_sh *sh)
{
	char	*tmp;

	while (token)
	{
		tmp = token->content;
		if (!ft_strcmp(tmp, "<<"))
		{
			token = set_delim_type(token);
			tmp = token->content;
		}
		if (is_quote(*tmp) || (*tmp == '$' && is_quote(*(tmp + 1))))
		{
			token->content = expand_quotes(tmp, sh);
			free(tmp);
		}
		else if (ft_strchr(tmp, '$') && ft_strlen(tmp) > 1)
		{
			token->content = expand_string(tmp, sh);
			free(tmp);
		}
		token = token->next;
	}
}
