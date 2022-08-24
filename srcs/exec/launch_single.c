/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:07:55 by user42            #+#    #+#             */
/*   Updated: 2022/08/24 21:56:26 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern uint8_t	g_last_status;

static void	launch_single_cmd(t_sh *sh, t_cmd *cmd)
{
	pid_t	pid;

	signal_catching_mode(PARENT_PROCESS);
	pid = fork();
	if (pid < 0)
		error_display("fork", strerror(errno), 0);
	else if (pid == 0)
	{
		signal_catching_mode(CHILD_PROCESS);
		if (dup_io_singlecmd(cmd) == FAIL)
			exit_clear_child(sh, WRONG_REDIR);
		if (!cmd->args[0])
			exit_clear_child(sh, 0);
		cmd_execve(sh, cmd);
	}
	else
		wait_children(sh, pid);
}

void	launch_single(t_sh *sh, t_cmd *cmd)
{
	if (cmd->built_i > -1)
		launch_single_builtin(sh, cmd);
	else
		launch_single_cmd(sh, cmd);
}
