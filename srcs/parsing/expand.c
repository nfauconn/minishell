/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:35:18 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/16 09:51:06 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern unsigned char	g_last_status;

void	add_to_new(t_newstr *new, t_newstr *to_add)
{
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
	char		*start;
	char		*end;
	t_newstr	to_add;

	new.str = NULL;
	new.len = 0;
	to_add.str = NULL;
	to_add.len = 0;
	end = ptr + len;
 	while (*ptr && ptr != end)
	{
		if (*ptr == '$')
		{
			ptr++;
			if (ptr != end)
			{
				to_add.str = expand_var(&ptr, sh);
				to_add.len = ft_strlen(to_add.str);
			}
		}
		else
		{
			start = ptr;
			while (*ptr && ptr != end && *ptr != '$')
				ptr++;
			to_add.len = ptr - start;
			to_add.str = ft_substr(start, 0, to_add.len);
		}
		add_to_new(&new, &to_add);
	}
	return (new.str);
}

char	*expand(char *ptr, t_sh *sh)
{
	t_newstr	new;
	t_indexes	i;
	t_newstr	to_add;

	new.str = NULL;
	new.len = 0;
	i.curr = 0;
	while (ptr[i.curr])
	{
		i.start = i.curr;
		if (is_quote(ptr[i.curr]) || is_doll_then_quote(&ptr[i.curr]))
		{
			if (ptr[i.curr] == '$')
				i.curr++;
			i.start = i.curr;
			if (ptr[i.curr] == '\'')
			{
				i.curr++;
				while (ptr[i.curr] != '\'')
					i.curr++;
				i.curr++;
				to_add.len = i.curr - i.start;
				to_add.str = ft_substr(ptr, i.start, to_add.len);
			}
			else if (ptr[i.curr] == '\"')
			{
				i.curr++;
				while (ptr[i.curr] != '\"')
					i.curr++;
				i.curr++;
				to_add.len = i.curr - i.start;
				to_add.str = expand_str(ptr + i.start, to_add.len, sh);
			}
		}
		else
		{
			while (ptr[i.curr] && !is_quote(ptr[i.curr])
				&& !is_doll_then_quote(&ptr[i.curr]))
				i.curr++;
			to_add.len = i.curr - i.start;
			to_add.str = expand_str(ptr + i.start, to_add.len, sh);
		}
		add_to_new(&new, &to_add);
	}
	return (new.str);
}

/* WORKING EXCEPT FOR SIMPLE QUOTES IN DB QUOTES :}
char	*expand(char *ptr, t_sh *sh)
{
	t_newstr	new;
	t_indexes	i;
	char		*to_add;

	new.str = NULL;
	new.len = 0;
	i.curr = 0;
	while (ptr[i.curr])
	{
		i.start = i.curr;
		if (ptr[i.curr] == '\'')
		{
			i.curr++;
			while (ptr[i.curr] != '\'')
				i.curr++;
			i.curr++;
			to_add = ft_substr(ptr, i.start, i.curr - i.start);
		}
		else
		{
			while (ptr[i.curr] && ptr[i.curr] != '\'')
				i.curr++;
			to_add = expand_str(ptr + i.start, i.curr - i.start, sh);
		}
		add_to_new(&new, to_add);
	}
	return (new.str);
} */
