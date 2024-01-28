/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:25:43 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/14 16:09:28 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_builtins_ptr(t_sh *sh)
{
	sh->exec_built[cd] = &mini_cd;
	sh->exec_built[echo] = &mini_echo;
	sh->exec_built[env] = &mini_env;
	sh->exec_built[exit2] = &mini_exit;
	sh->exec_built[export] = &mini_export;
	sh->exec_built[pwd] = &mini_pwd;
	sh->exec_built[unset] = &mini_unset;
}

void	init_sh(t_sh *sh)
{
	sh->level = 0;
	sh->cmd_nb = 0;
	sh->cmd_list = NULL;
	sh->heredoc_nb = 0;
	sh->env = NULL;
	init_builtins_ptr(sh);
}
