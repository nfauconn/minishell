/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:35:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/18 23:39:05 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern unsigned char	g_last_status;

void	add_to_new(t_newstr *new, t_newstr *to_add)
{
	if (to_add->str)
		to_add->len = ft_strlen(to_add->str);
	new->len += to_add->len;
	new->str = ft_reallocstr(new->str, new->len);
	if (to_add->str)
		ft_strlcat(new->str, to_add->str, new->len + 1);
	free(to_add->str);
}

char	*var_value(char *var_name, size_t len, t_list *env)
{
	char	*env_line;

	while (env)
	{
		env_line = (char *)env->content;
		if (!ft_strncmp(var_name, env_line, len) && (env_line)[len] == '=')
			return (ft_strdup(ft_strchr(env_line, '=') + 1));
		env = env->next;
	}
	return (NULL);
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
		else
			(*ptr)++;
	}
	return (ft_strdup(""));
}

char	*expand_str(char *ptr, size_t len, t_sh *sh)
{
	t_newstr	new;
	t_charptr	p;
	t_newstr	to_add;

	new = ft_initnewstr();
	to_add = ft_initnewstr();
	p.end = ptr + len;
	while (*ptr && ptr != p.end)
	{
		if (*ptr == '$' && (ptr + 1) != p.end)
		{
			ptr++;
			to_add.str = expand_var(&ptr, sh);
		}
		else if (*ptr == '$' && ++ptr == p.end)
			to_add.str = ft_strdup("$");
		else
		{
			p.start = ptr;
			while (*ptr && ptr != p.end && *ptr != '$')
				ptr++;
			to_add.str = ft_substr(p.start, 0, ptr - p.start);
		}
		add_to_new(&new, &to_add);
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
		printf("ret expanded in handle quoted: %s\n", ret);
		int i = 1;
		while (ret[i] && ret[i + 1])
		{
			if (ret[i] == '\"')
				ret[i] *= -1;
			i++;
		}
//		printf("ret expanded in handle quoted: %s\n", ret);

	}
	return (ret);
}

// before return (ret):
//	ft_replacefree(&ret, ft_substr(ret, 1, ft_strlen(ret) - 1));
// ??????????? pour regler quotes inside quotes apres expand ??
// ou technique d ismael, char *= -1 a l interieur des quotes

char	*expand(char *ptr, t_sh *sh)
{
	t_newstr	new;
	t_indexes	i;
	t_newstr	to_add;

	new = ft_initnewstr();
	i.curr = 0;
	while (ptr[i.curr])
	{
		i.start = i.curr;
		if (is_quote(ptr[i.curr]) || is_doll_then_quote(&ptr[i.curr]))
		{
			to_add.str = handle_quoted(ptr, &i, sh);
		}
		else
		{
			while (ptr[i.curr] && !is_quote(ptr[i.curr])
				&& !is_doll_then_quote(&ptr[i.curr]))
				i.curr++;
			to_add.str = expand_str(ptr + i.start, i.curr - i.start, sh);
		}
		add_to_new(&new, &to_add);
	}
	return (new.str);
}
