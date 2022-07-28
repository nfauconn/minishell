/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:46:29 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/28 20:30:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "clearexit.h"

static void	exit_clear(t_sh *sh, unsigned char exit_code)
{
	if (sh->cmd_nb == 1)
	{
		ft_printerror("exit\n");
		exit_clear_process(sh, exit_code);
	}
	else
		exit_clear_process(sh, exit_code);
}

int	mini_exit(t_sh *sh, t_cmd *cmd)
{
	int	i;
	int	exit_code;

	i = 0;
	while (cmd->args[i])
		i++;
	if (i == 1)
		exit_clear(sh, 0);
	else if (i == 2 && !ft_str_isdigit(cmd->args[1]))
	{
		error_display("exit", cmd->args[1], ": numeric argument required");
		exit_clear(sh, 2);
	}
	else if (i > 2)
	{
		error_display("exit", "too many arguments", 0);
		return (1);
	}
	else
	{
		exit_code = ft_atoi(cmd->args[1]);
		exit_clear(sh, exit_code);
	}
	return (1);
}
