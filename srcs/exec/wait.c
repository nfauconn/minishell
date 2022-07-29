/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:07:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/30 01:51:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern unsigned char	g_last_status;

void	wait_heredoc(void)
{
	pid_t	pid;
	int		status;
	int		signal;

	pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			ft_printerror("\n");
		g_last_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		g_last_status = signal + 128;
	}
}

void	wait_child(t_sh *sh, size_t cmd_index)
{
	pid_t	pid;
	int		status;
	int		signal;

	pid = waitpid(-1, &status, 0);
	if (pid < 0)
	{
		error_display("waitpid", strerror(errno), 0);
		exit_clear_minish(sh, EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		g_last_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGSEGV)
			ft_printerror("Segmentation fault (core dumped)\n");
		else if (signal == SIGBUS)
			ft_printerror("Bus error (core dumped)\n");
		else if (signal == SIGINT)
			ft_printerror("\n");
		else if (signal == SIGQUIT)
		{
			if (cmd_index == sh->cmd_nb || sh->cmd_nb == 1)
				ft_printerror("Quit (core dumped)\n");
		}
		g_last_status = signal + 128;
	}
}

void	wait_children(t_sh *sh)
{
	t_cmd	*cmd;
	size_t	i;

	i = 0;
	cmd = sh->cmd_list;
	while (i < sh->cmd_nb && cmd)
	{
		wait_child(sh, cmd->index);
		i++;
		cmd = cmd->next;
	}
}
