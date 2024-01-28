/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:00:06 by noe               #+#    #+#             */
/*   Updated: 2022/09/08 18:07:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_bool	init_shell_var(t_list *env)
{
	char		*binary_name;
	char		*tmp_cwd;
	t_newstr	shell_val;

	tmp_cwd = getcwd(NULL, 0);
	if (!tmp_cwd)
		return (1);
	shell_val.str = ft_strjoin("SHELL=", tmp_cwd);
	free(tmp_cwd);
	if (!shell_val.str)
		return (1);
	shell_val.len = ft_strlen(shell_val.str);
	binary_name = ft_strdup("/./minishell");
	realloc_cat(&shell_val, binary_name);
	do_export(&env, shell_val.str);
	free(shell_val.str);
	return (0);
}

static t_bool	init_shell_level(t_list *env)
{
	char	*lvl_str;
	int		lvl_int;
	char	*shlvl;

	lvl_int = 0;
	lvl_str = var_value("SHLVL", 5, env);
	if (!lvl_str)
		return (1);
	lvl_int = ft_atoi(lvl_str);
	ft_strdel(&lvl_str);
	lvl_int++;
	lvl_str = ft_itoa(lvl_int);
	if (!lvl_str)
		return (1);
	shlvl = ft_strjoin("SHLVL=", lvl_str);
	if (!shlvl)
	{
		free(lvl_str);
		return (1);
	}
	do_export(&env, shlvl);
	free(shlvl);
	free(lvl_str);
	return (0);
}

static t_bool	create_minimal_env(t_list **head)
{
	char	*content;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	content = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (!content)
		return (1);
	ft_lstadd_back(head, ft_lstnew((void *)content));
	content = ft_strdup("SHLVL=1");
	if (!content)
		return (1);
	ft_lstadd_back(head, ft_lstnew((void *)content));
	content = ft_strdup("_=/usr/bin/env");
	if (!content)
		return (1);
	ft_lstadd_back(head, ft_lstnew((void *)content));
	content = ft_strdup("OLDPWD");
	if (!content)
		return (1);
	ft_lstadd_back(head, ft_lstnew((void *)content));
	return (0);
}

t_list	*init_env(char **env_tab)
{
	t_list	*env;

	env = NULL;
	if (env_tab && *env_tab)
	{
		env = ft_strarraytolist(env_tab);
		if (!env || init_shell_level(env) || init_shell_var(env))
		{
			ft_strarrayclear(&env_tab);
			ft_lstclear(&env, free);
			return (NULL);
		}
	}
	else
	{
		if (create_minimal_env(&env))
			return (NULL);
	}
	return (env);
}
