/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:46:29 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/22 20:29:10 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	mini_exit(t_sh *sh, t_cmd *cmd)
{
	int	i;
	int	exit_code;

	i = 0;
	ft_printerror("exit\n");
	while (cmd->args[i])
		i++;
	if (i == 1)
		exit_clear(sh, 0);
	if (cmd->args[1] && !ft_str_isdigit(cmd->args[1]))
	{
		error_display("exit", cmd->args[1], ": numeric argument required");
		exit_clear(sh, 2);
	}
	if (i > 2)
	{
		error_display("exit", "too many arguments", 0);
		return (1);
	}
	exit_code = ft_atoi(cmd->args[1]);
	exit_clear(sh, exit_code);
	return (0);
}
