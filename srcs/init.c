/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:25:43 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/09 18:49:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_input(t_input *input)
{
	input->line_read = get_input();
	input->token_list = NULL;
}

void	init_sh(t_sh *sh, char **env)
{
	sh->cmd_nb = 0;
	sh->cmd = NULL;
	sh->env = NULL;
	sh->env = tab_to_lst(env);
}
