/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:25:43 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/09 21:12:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	init_shell_level(t_list *env)
{
	char	*lvl_str;
	int		lvl_int;
	char	*shlvl;

	lvl_int = 0;
	lvl_str = var_value("SHLVL", 5, env);
	if (lvl_str)
	{
		lvl_int = ft_atoi(lvl_str);
		ft_strdel(&lvl_str);
	}
	lvl_int++;
	lvl_str = ft_itoa(lvl_int);
	shlvl = ft_strjoin("SHLVL=", lvl_str);
	do_export(&env, shlvl);
	free(shlvl);
	free(lvl_str);
} */

static void	create_minimal_env(t_list **head)
{
	char	*content;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	content = ft_strjoin("PWD=", tmp);
	free(tmp);
	ft_lstadd_back(head, ft_lstnew((void *)content));
	content = ft_strdup("SHLVL=0");
	ft_lstadd_back(head, ft_lstnew((void *)content));
	content = ft_strdup("_=/usr/bin/env");
	ft_lstadd_back(head, ft_lstnew((void *)content));
	content = ft_strdup("OLDPWD");
	ft_lstadd_back(head, ft_lstnew((void *)content));
}

t_list	*init_env(char **env_tab)
{
	t_list	*env;

	env = NULL;
	if (env_tab && *env_tab)
	{
		env = ft_strarraytolist(env_tab);
//		init_shell_level(env);
	}
	else
		create_minimal_env(&env);
	return (env);
}

static void	init_builtins_ptr(t_sh *sh)
{(void)sh;
/* 	sh->exec_built[cd] = &mini_cd;
	sh->exec_built[echo] = &mini_echo;
	sh->exec_built[env] = &mini_env;
	sh->exec_built[exit2] = &mini_exit;
	sh->exec_built[export] = &mini_export;
	sh->exec_built[pwd] = &mini_pwd;
	sh->exec_built[unset] = &mini_unset; */	
}

void	init_sh(t_sh *sh)
{
	sh->level = 0;
	sh->line_nb = 0;
	sh->cmd_nb = 0;
	sh->cmd_list = NULL;
	sh->heredoc_nb = 0;
	sh->env = NULL;
	init_builtins_ptr(sh);
}
