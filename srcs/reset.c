/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:38:56 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/27 22:54:34 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_input(t_sh *sh, t_input *input)
{
	if (input)
		clear_input(input);
	if (sh->cmd_list)
		clear_cmd_list(sh->cmd_list);
	sh->cmd_nb = 0;
	sh->heredoc_nb = 0;
}