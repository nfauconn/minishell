/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:25:43 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/14 18:19:18 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_input(t_input *input)
{
	input->line_read = get_input();
	if (!input->line_read)
		return (FAILURE);
	input->token_list = NULL;
	return (0);
}

void	init_sh(t_sh *sh, char **env)
{
	sh->cmd_nb = 0;
	sh->cmd_list = NULL;
	sh->env = NULL;
	sh->env = tab_to_lst(env);
}
