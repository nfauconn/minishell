/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:01:12 by user42            #+#    #+#             */
/*   Updated: 2022/07/05 16:45:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtin(t_sh *sh, t_cmd *cmd)
{
	int	ret;

	if ((cmd->built_i == cd || cmd->built_i == export || cmd->built_i == unset)
		&& cmd->next)
		exit(0);//and close ?
	ret = sh->exec_built[cmd->built_i](sh, cmd);
	close(1);//?
	exit(ret);
}
