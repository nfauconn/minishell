/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:35:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/26 16:44:06 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern uint8_t	g_last_status;

void	add_to_new(t_newstr *new, char *to_add)
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
	while (*ptr && ptr != p.end)
	{
 		if (*ptr == '$' && (ptr + 1) != p.end)
		{
			ptr++;
			to_add = expand_var(&ptr, sh);
		}
		else if (*ptr == '$' && ++ptr == p.end)
			to_add = ft_strdup("$");
		else
		{
			p.start = ptr;
			if (is_blank(*(p.start)) && p.start + 1 == p.end)
				return (new.str);
			while (*ptr && ptr != p.end && *ptr != '$')
				ptr++;
			to_add = ft_substr(p.start, 0, ptr - p.start);
		}
		add_to_new(&new, to_add);
	}
	return (new.str);
}

static char	*handle_quoted(char *ptr, t_indexes *i, t_sh *sh)
{
	char	*ret;

	ret = NULL;
	if (ptr[i->curr] == '$')
		i->curr++;
	i->start = i->curr;
	if (ptr[i->curr] == '\'')
	{
		i->curr++;
		while (ptr[i->curr] != '\'')
			i->curr++;
		i->curr++;
		ret = ft_substr(ptr, i->start, i->curr - i->start);
	}
	else if (ptr[i->curr] == '\"')
	{
		i->curr++;
		while (ptr[i->curr] != '\"')
			i->curr++;
		i->curr++;
		ret = expand_str(ptr + i->start, i->curr - i->start, sh);
	}
	return (ret);
}

char	*expand(char *ptr, t_sh *sh)
{
	t_newstr	new;
	t_indexes	i;
	char		*to_add;

	new = ft_initnewstr();
	i.curr = 0;
	while (ptr[i.curr])
	{
		i.start = i.curr;
		if (is_quote(ptr[i.curr]) || is_doll_then_quote(&ptr[i.curr]))
		{
			to_add = handle_quoted(ptr, &i, sh);
		}
		else
		{
			while (ptr[i.curr] && !is_quote(ptr[i.curr])
				&& !is_doll_then_quote(&ptr[i.curr]))
				i.curr++;
			to_add = expand_str(ptr + i.start, i.curr - i.start, sh);
		}
		add_to_new(&new, to_add);
	}
	return (new.str);
}
