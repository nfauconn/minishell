/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/02 18:21:16 by mdankou          ###   ########.fr       */
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
			if (!ft_strncmp(var_name, str, var_len) && (str[var_len] == '='
					|| str[var_len] == '\0'))
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

static int	is_valid_identifier(char *str)
{
	size_t	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		++i;
	}
	return (1);
}

static void	do_unset(t_sh *sh, char *id)
{
	int		var_len;
	t_list	*elm;

	var_len = ft_strlen(id);
	if (!ft_strncmp(id, sh->env->content, var_len)
		&& (((char *)sh->env->content)[var_len] == '='
		|| ((char *)sh->env->content)[var_len] == '\0'))
	{
		elm = sh->env;
		sh->env = sh->env->next;
		ft_lstdelone(elm, free);
	}
	else
		del_elm_mid(sh->env, id);
}

int	mini_unset(t_sh *sh, t_cmd *cmd)
{
	size_t	j;
	int		status;
	char	**var_name;

	var_name = cmd->args;
	j = 0;
	status = 0;
	while (var_name && var_name[++j])
	{
		if (!is_valid_identifier(var_name[j]))
		{
			ft_printerror("export: `%s': not a valid identifier\n",
				var_name[j]);
			status = 1;
		}
		else if (sh->env)
			do_unset(sh, var_name[j]);
	}
	return (status);
}
