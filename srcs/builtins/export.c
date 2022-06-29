/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/29 20:26:24 by user42           ###   ########.fr       */
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

int	mini_export(t_sh *sh, t_cmd *cmd)
{
	int		status;
	size_t	j;

	char	**var_assigns = cmd->args;
	j = 0;
	status = 0;
	while (var_assigns && var_assigns[++j])
	{
		do_export(&sh->env, var_assigns[j]);
	}
	return (status);
}
