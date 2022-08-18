/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:38:56 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/19 01:16:03 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reset.h"

void	reset_sh(t_sh *sh)
{
	if (sh->cmd_list)
		clear_cmd_list(&sh->cmd_list);
	sh->cmd_list = NULL;
	sh->cmd_nb = 0;
	sh->heredoc_nb = 0;
}
