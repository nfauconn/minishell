/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/19 12:34:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_list **env, char **var_assign)
{
	size_t	j;
	t_list	*l;
	char	*str;
	int		var_len;

	j = -1;
	while (var_assign[++j])
	{
		if (!strchr(var_assign[j], '='))
			continue;
		l = (t_list *)(*env);
		while (l)
		{
			str = (char *)l->content;
			var_len = ft_strlen(var_assign[j]);
			if (!ft_strncmp(var_assign[j], str, var_len)
				&& str[var_len] == '\0')
			{
				l->content = ft_strdup(var_assign[j]);
				break ;
			}
			l = l->next;
		}
		if (!l)
			ft_lstadd_back(env, ft_lstnew(ft_strdup(var_assign[j])));
	}
	return (0);
}
