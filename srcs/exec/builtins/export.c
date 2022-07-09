/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/09 16:36:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	do_export(t_list **env, char *assign)
{
	t_list	*l;
	char	*str;
	u_int	var_len;

	var_len = strchr(assign, '=') - assign;
	if (var_len <= 0)
		return ;
	l = (t_list *)(*env);
	while (l)
	{
		str = (char *)l->content;
		if (!ft_strncmp(assign, str, var_len) && str[var_len] == '=')
		{
			l->content = ft_strdup(assign);
			free(str);
			break ;
		}
		l = l->next;
	}
	if (!l)
		ft_lstadd_back(env, ft_lstnew(ft_strdup(assign)));
}

int	mini_export(t_sh *sh, t_cmd *cmd)
{
	char	**var_assigns;
	int		status;
	size_t	j;

	var_assigns = cmd->args;
	j = 0;
	status = 0;
	while (var_assigns && var_assigns[++j])
	{
		do_export(&sh->env, var_assigns[j]);
	}
	return (status);
}
