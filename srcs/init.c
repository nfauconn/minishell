/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:25:43 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/24 01:26:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_input(t_sh *sh, t_input *input)
{
	input->line_read = get_input(sh);
	if (!input->line_read)
		return (FAILURE);
	input->token_list = NULL;
	return (0);
}

static void	init_shell_level(t_list *env)
{
	char	*lvl_str;
	int		lvl_int;
	char	*shlvl;

	lvl_str = var_value("SHLVL", 5, env);
	lvl_int = ft_atoi(lvl_str);
	lvl_int++;
	lvl_str = ft_itoa(lvl_int);
	shlvl = ft_strjoin("SHLVL=", lvl_str);
	do_export(&env, shlvl);
	free(shlvl);
	free(lvl_str);
}

static t_list	*init_env(char **env_tab)
{
	t_list	*env;
	t_list	*head;

	if (env_tab && *env_tab)
	{
		ft_str_array_display(env_tab);
		head = ft_str_array_to_lst(env_tab);
		init_shell_level(head);
	}
	else
	{
		head = ft_lstnew(getcwd(NULL, 0));
		ft_lstadd_back(&head, head);
		env = head;
		env = env->next;
		env = ft_lstnew("SHLVL=1");
		ft_lstadd_back(&head, env);
		env = env->next;
		env = ft_lstnew("_=/usr/bin/env");
		ft_lstadd_back(&head, env);
		env->next = NULL;
	}
	return (head);
}

void	init_sh(t_sh *sh, char **env_sh)
{
	sh->cmd_nb = 0;
	sh->cmd_list = NULL;
	sh->heredoc_nb = 0;
	sh->env = NULL;
	sh->env = init_env(env_sh);
	sh->last_status = 0;
	sh->last_status_str = NULL;
	sh->exec_built[cd] = &mini_cd;
	sh->exec_built[echo] = &mini_echo;
	sh->exec_built[env] = &mini_env;
	sh->exec_built[exit2] = &mini_exit;
	sh->exec_built[export] = &mini_export;
	sh->exec_built[pwd] = &mini_pwd;
	sh->exec_built[unset] = &mini_unset;
}
