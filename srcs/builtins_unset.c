/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/18 17:53:51 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*False: Incomplete*/

/*Faire une fontion search_previous pourrait etre une bonne idee*/

int unset(void *env, char **var_name)
{
	size_t	j;
	t_list	*l;
	t_list	*elm;
	char	*str;
	int	var_len;

	j = 0;
	l = (t_list *)env;
	str = (char *)l->content;
	var_len = strlen(var_name[j]);
	if (!((t_list *)env)->next && !ft_strncmp(var_name[j], str, var_len)
		&& str[var_len] == '\0')
	{
		ft_lstclear((t_list **)&env, free);
		return (0);
	}
	while (var_name[j])
	{
		l = (t_list *)env;
		while (l)
		{
			elm = l->next;
			if (elm)
			{
				str = (char *)elm->content;
				var_len = strlen(var_name[j]);
				if (!ft_strncmp(var_name[j], str, var_len)
					&& str[var_len] == '\0')
				{
					break;	
				}
			}
			l = l->next;
		}
		l->next = elm->next;
		ft_lstdelone(elm, free);
		++j;
	}
	return (0);
}