/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:13:48 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/31 13:05:15 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
