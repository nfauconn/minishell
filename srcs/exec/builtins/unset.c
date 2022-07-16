/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/16 15:58:30 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

int	mini_unset(t_sh *sh, t_cmd *cmd)
{
	size_t	j;
	int		var_len;
	t_list	*l;
	t_list	*elm;
	char	**var_name;

	var_name = cmd->args;
	j = 0;
	while (var_name && var_name[++j])
	{
		l = sh->env;
		if (!l)
			return (0);
		var_len = ft_strlen(var_name[j]);
		if (!ft_strncmp(var_name[j], l->content, var_len)
			&& ((char *)l->content)[var_len] == '=')
		{
			elm = sh->env;
			sh->env = sh->env->next;
			ft_lstdelone(elm, free);
		}
		else
			del_elm_mid(l, var_name[j]);
	}
	return (0);
}
