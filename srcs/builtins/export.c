/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/22 16:33:30 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_export(t_list **env, char *assign)
{
	t_list	*l;
	char	*str;
	int		var_len;

	if (!strchr(assign, '='))
		return ;
	l = (t_list *)(*env);
	while (l)
	{
		str = (char *)l->content;
		var_len = ft_strlen(assign);
		if (!ft_strncmp(assign, str, var_len) && !str[var_len])
		{
			l->content = ft_strdup(assign);
			break ;
		}
		l = l->next;
	}
	if (!l)
		ft_lstadd_back(env, ft_lstnew(ft_strdup(assign)));
}

int	builtin_export(t_list **env, char **var_assigns)
{
	int		status;
	size_t	j;

	j = -1;
	status = 0;
	while (var_assigns[++j])
	{
		do_export(env, var_assigns[j]);
	}
	return (status);
}
