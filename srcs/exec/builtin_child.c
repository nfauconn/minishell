/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:01:12 by user42            #+#    #+#             */
/*   Updated: 2022/06/30 10:03:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_child(t_sh *sh, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (cmd->built_i == echo)
	{
		ret = mini_echo(sh, cmd);
	}
	return (ret);
}
