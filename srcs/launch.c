/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:05:21 by user42            #+#    #+#             */
/*   Updated: 2022/07/05 15:27:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch(t_sh *sh)
{
	if (!sh->cmd_list || sh->cmd_nb == 0)
		return (sh->last_status);
	if (sh->cmd_nb == 1)
	{
		if (sh->cmd_list->built_i > -1)
			single_builtin_seq(sh, sh->cmd_list);
		else
			single_cmd_seq(sh, sh->cmd_list);
	}
	else
		pipeline_seq(sh, sh->cmd_list);
	return (sh->last_status);
}
