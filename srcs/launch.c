/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:05:21 by user42            #+#    #+#             */
/*   Updated: 2022/06/30 09:47:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch(t_sh *sh)
{
	if (sh->cmd_nb == 1 && sh->cmd_list->built_i > -1)
		single_builtin_exec(sh, sh->cmd_list);
	else
		subshells_seq(sh, sh->cmd_list);
	return (sh->last_status);
}
