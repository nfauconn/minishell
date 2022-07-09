/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:07:55 by user42            #+#    #+#             */
/*   Updated: 2022/07/09 19:14:34 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	launch_single_builtin(t_sh *sh, t_cmd *cmd)
{
/* 	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO); */

// ==> CHECKER LES REDIR DANS ECHO MAIS SI ON DUP APRES ON EST FOUTU VU QU ON A PAS FORK
	signal_catching_mode(SH_PROCESS);
	sh->last_status = sh->exec_built[cmd->built_i](sh, cmd);
	signal_catching_mode(INTERACTIVE);
	return (sh->last_status);
}

static void	redir_single(t_sh *sh, t_cmd *cmd)
{
	if (cmd->redir_in == REDIR_FAIL || cmd->redir_out == REDIR_FAIL)
		exit_clear(sh, WRONG_REDIR);
	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
}

static int	launch_single_cmd(t_sh *sh, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (exec_error("fork: ", strerror(errno)));
	if (pid == 0)
	{
		signal_catching_mode(CHILD_PROCESS);
		redir_single(sh, cmd);
		cmd_execve(sh, cmd);
	}
	wait_children(sh);
	signal_catching_mode(INTERACTIVE);
	return (sh->last_status);
}

void	launch_single(t_sh *sh, t_cmd *cmd)
{
	if (cmd->built_i > -1)
		launch_single_builtin(sh, cmd);
	else
		launch_single_cmd(sh, cmd);
}
