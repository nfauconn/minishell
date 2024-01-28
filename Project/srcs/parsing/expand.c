/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:35:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/14 22:13:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern uint8_t	g_last_status;

void	realloc_cat(t_newstr *new, char *to_add)
{
	size_t	len;

	len = ft_strlen(to_add);
	new->len += len;
	new->str = ft_reallocstr(new->str, new->len);
	if (to_add)
		ft_strlcat(new->str, to_add, new->len + 1);
	free(to_add);
}

char	*expand_var(char **ptr, t_sh *sh)
{
	char	*start;

	start = *ptr;
	if (*start)
	{
		if (*start == '?')
		{
			(*ptr)++;
			return (ft_itoa(g_last_status));
		}
		else if (is_identifier(*start) && !ft_isdigit(*start))
		{
			while (is_identifier(**ptr))
				(*ptr)++;
			return (var_value(start, (*ptr) - start, sh->env));
		}
		else if (!ft_isalnum(*start))
			return (ft_strdup("$"));
		else
			(*ptr)++;
	}
	return (ft_strdup(""));
}

char	*expand_str(char *ptr, size_t len, t_sh *sh)
{
	t_newstr	new;
	t_charptr	p;
	char		*to_add;

	new = ft_initnewstr();
	p.end = ptr + len;
	while (*ptr && ptr != p.end && len--)
	{
		if (*ptr == '$' && (ptr + 1) != p.end && ++ptr)
			to_add = expand_var(&ptr, sh);
		else if (*ptr == '$' && ++ptr == p.end)
			to_add = ft_strdup("$");
		else
		{
			p.start = ptr;
			while (*ptr && ptr != p.end && *ptr != '$')
				ptr++;
			to_add = ft_substr(p.start, 0, ptr - p.start);
		}
		realloc_cat(&new, to_add);
	}
	return (new.str);
}

static char	*handle_quoted(char **ptr, t_sh *sh)
{
	char	*ret;
	char	*start;

	ret = NULL;
	if (**ptr == '$')
		(*ptr)++;
	start = *ptr;
	if (**ptr == '\'')
	{
		(*ptr)++;
		while (**ptr != '\'')
			(*ptr)++;
		(*ptr)++;
		ret = ft_substr(start, 0, (*ptr) - start);
	}
	else if (**ptr == '\"')
	{
		(*ptr)++;
		while (**ptr != '\"')
			(*ptr)++;
		(*ptr)++;
		ret = expand_str(start, (*ptr) - start, sh);
	}
	return (ret);
}

char	*expand(char *ptr, t_sh *sh)
{
	t_newstr	new;
	char		*start;
	char		*to_add;

	new = ft_initnewstr();
	while (*ptr)
	{
		if (is_quote(*ptr) || is_doll_then_quote(ptr))
		{
			to_add = handle_quoted(&ptr, sh);
		}
		else
		{
			start = ptr;
			while (*ptr && !is_quote(*ptr) && !is_doll_then_quote(ptr))
				ptr++;
			to_add = expand_str(start, ptr - start, sh);
		}
		realloc_cat(&new, to_add);
	}
	return (new.str);
}
