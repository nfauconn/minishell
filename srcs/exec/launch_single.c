/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:07:55 by user42            #+#    #+#             */
/*   Updated: 2022/07/13 22:13:13 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redir.h"

static int	launch_single_builtin(t_sh *sh, t_cmd *cmd)
{
	if (open_single_cmd_redir(cmd) == FAILURE)
		return(WRONG_REDIR);
	if (cmd->redir_out == NO_REDIR)
		cmd->redir_out = STDOUT_FILENO;
	sh->last_status = sh->exec_built[cmd->built_i](sh, cmd);
	return (sh->last_status);
}

static int	launch_single_cmd(t_sh *sh, t_cmd *cmd)
{
	pid_t	pid;

	signal_catching_mode(PARENT_PROCESS);
	pid = fork();
	if (pid < 0)
		return (exec_error("fork: ", strerror(errno)));
	if (pid == 0)
	{
		signal_catching_mode(CHILD_PROCESS);
		single_cmd_redir(sh, cmd);
		cmd_execve(sh, cmd);
	}
	wait_children(sh);
	signal_catching_mode(PARENT_PROCESS);
	return (sh->last_status);
}

void	launch_single(t_sh *sh, t_cmd *cmd)
{
	if (cmd->built_i > -1)
		launch_single_builtin(sh, cmd);
	else
		launch_single_cmd(sh, cmd);
}
