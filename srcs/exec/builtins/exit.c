/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:46:29 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/09 18:24:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "exec.h"

int		mini_exit(t_sh *sh, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	if (i == 0)
		exit_clear(sh, 0);
	if (i > 1)
	{
		error_display("exit", "too many arguments");
		return (1);
	}
	ft_printerror("exit\n");
	exit_clear(sh, ft_atoi(cmd->args[1]));
	return (0);
}

