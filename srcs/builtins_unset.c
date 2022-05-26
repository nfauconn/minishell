/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/26 13:18:06 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_elm_mid(t_list	*l, char *var_name)
{
	t_list	*elm;
	char	*str;
	int		var_len;

	while (l)
	{
		elm = l->next;
		if (elm)
		{
			str = (char *)elm->content;
			var_len = strlen(var_name);
			if (!ft_strncmp(var_name, str, var_len) && str[var_len] == '=')
				break ;
		}
		l = l->next;
	}
	if (elm)
	{
		l->next = elm->next;
		ft_lstdelone(elm, free);
	}
}

int	unset(t_list **env, char **var_name)
{
	size_t	j;
	t_list	*l;
	t_list	*elm;
	char	*str;
	int		var_len;

	j = -1;
	while (var_name[++j])
	{
		if (!*env)
			return (0);
		l = (t_list *)(*env);
		str = (char *)l->content;
		var_len = ft_strlen(var_name[j]);
		if (!ft_strncmp(var_name[j], str, var_len) && str[var_len] == '=')
		{
			elm = (*env);
			(*env) = (*env)->next;
			ft_lstdelone(elm, free);
		}
		else
			del_elm_mid(l, var_name[j]);
	}
	return (0);
}
