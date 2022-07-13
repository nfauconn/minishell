/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:07:55 by user42            #+#    #+#             */
/*   Updated: 2022/07/13 14:42:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	open_redir(t_cmd *cmd)
{
	errno = 0;
	cmd->redir_in = NO_REDIR;
	cmd->redir_out = NO_REDIR;
	if (cmd->redir_error)
	{
		error_display(cmd->redir_error, 0, 0);
		return (1);;
	}
	if (cmd->infile)
	{
		cmd->redir_in = open(cmd->infile, O_RDONLY);
		if (cmd->redir_in == WRONG_REDIR)
		{
			error_display(cmd->infile, strerror(errno), 0);
			return (1);;
		}
	}
	if (cmd->outfile)
	{
		if (cmd->redir_out_type == APPEND_FILE)
			cmd->redir_out = open(cmd->outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			cmd->redir_out = open(cmd->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (cmd->redir_out == WRONG_REDIR)
		{
			error_display(cmd->outfile, strerror(errno), 0);
			return (1);;
		}
	}
	return (0);
}

static int	launch_single_builtin(t_sh *sh, t_cmd *cmd)
{
	if (open_redir(cmd) == FAILURE)
		return(WRONG_REDIR);
	if (cmd->redir_out == NO_REDIR)
		cmd->redir_out = STDOUT_FILENO;
	sh->last_status = sh->exec_built[cmd->built_i](sh, cmd);
	return (sh->last_status);
}

static void	redir_single(t_sh *sh, t_cmd *cmd)
{
	if (open_redir(cmd) == FAILURE)
		exit_clear(sh, WRONG_REDIR);
	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
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
		redir_single(sh, cmd);
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
