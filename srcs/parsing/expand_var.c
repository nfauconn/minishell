/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:41:54 by user42            #+#    #+#             */
/*   Updated: 2022/08/13 19:54:51 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern unsigned char	g_last_status;

char	*var_value(char *str, size_t len, t_list *env)
{
	char	*env_line;

	while (env)
	{
		env_line = (char *)env->content;
		if (!ft_strncmp(str, env_line, len) && (env_line)[len] == '=')
			return (ft_strdup(ft_strchr(env_line, '=') + 1));
		env = env->next;
	}
	return (NULL);
}

char	*expanded_content(char **s, t_sh *sh)
{
	char	*start;

	start = *s;
	if (*start)
	{
		if (*start == '?')
		{
			(*s)++;
			return (ft_itoa(g_last_status));
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
