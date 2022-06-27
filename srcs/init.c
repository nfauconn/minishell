/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:25:43 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/27 15:44:39 by nfauconn         ###   ########.fr       */
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

void	init_sh(t_sh *sh, char **env)
{
	sh->cmd_nb = 0;
	sh->cmd_list = NULL;
	sh->env = NULL;
	sh->env = ft_str_array_to_lst(env);
	sh->last_status = 0;
	sh->last_status_str = NULL;
}
