/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:07:55 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 11:50:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern unsigned char	g_last_status;

static void	launch_single_cmd(t_sh *sh, t_cmd *cmd)
{
	pid_t	pid;

	signal_catching_mode(PARENT_PROCESS);
	pid = fork();
	if (pid < 0)
		exec_perror("fork", strerror(errno));
	if (pid == 0)
	{
		signal_catching_mode(CHILD_PROCESS);
		if (single_cmd_redir(cmd) == FAILURE)
			exit_clear_child(sh, WRONG_REDIR);
		if (!cmd->name)
			exit_clear_child(sh, g_last_status);
		cmd_execve(sh, cmd);
	}
	wait_children(sh);
	signal_catching_mode(PARENT_PROCESS);
}

void	launch_single(t_sh *sh, t_cmd *cmd)
{
	if (cmd->built_i > -1)
		launch_single_builtin(sh, cmd);
	else
		launch_single_cmd(sh, cmd);
}
