/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:54:26 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/18 17:54:31 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int export(void *env, char **var_assign)
{
	size_t	j;
	t_list	*l;
	char	*str;
	int	var_len;

	j = 0;
	while (var_assign[j])
	{
		l = (t_list *)env;
		while (l)
		{
			str = (char *)l->content;
			var_len = strlen(var_assign[j]);
			if (!ft_strncmp(var_assign[j], str, var_len)
				&& str[var_len] == '\0')
			{
				l->content = ft_strdup(str);
				break;
			}
			l = l->next;
		}
		if (!l)
			ft_lstadd_back((t_list **)&env, ft_lstnew(ft_strdup(str)));
		++j;
	}
	return (0);

}
