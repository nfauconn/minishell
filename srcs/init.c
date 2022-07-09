/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:25:43 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/09 18:12:51 by nfauconn         ###   ########.fr       */
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

void	init_sh(t_sh *sh, char **env_sh)
{
	sh->cmd_nb = 0;
	sh->cmd_list = NULL;
	sh->env = NULL;
	sh->env = ft_str_array_to_lst(env_sh);
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
