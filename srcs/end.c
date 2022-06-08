/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:09:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/08 14:17:50 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_sh(t_sh *sh)
{
	(void)sh;
/* 	if (sh->env)
		ft_lstclear(&sh->env, free);	 */
}

void	end_input(t_input *input)
{
	if (input->line_read)
		ft_strdel(&input->line_read);
	if (input->token_list)
		ft_lstclear(&input->token_list, free);
	input = NULL;
}

void	end(t_input *input, t_sh *sh)
{
	if (input)
		end_input(input);
	if (sh)
		end_sh(sh);
}