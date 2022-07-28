/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:05:21 by user42            #+#    #+#             */
/*   Updated: 2022/07/27 19:42:21 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	launch(t_sh *sh)
{
	if (sh->cmd_list && sh->cmd_nb != 0)
	{
		if (sh->cmd_nb == 1)
			launch_single(sh, sh->cmd_list);
		else
			launch_pipeline(sh, sh->cmd_list);
	}
}
