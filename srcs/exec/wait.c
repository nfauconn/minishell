/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:07:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/20 00:28:04 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern uint8_t	g_last_status;

t_bool	wait_heredoc(void)
{
	pid_t	pid;
	int		status;
	int		signal;

	pid = waitpid(-1, &status, 0);
	if (pid < 0)
		error_display("waitpid", strerror(errno), 0);
	if (WIFEXITED(status))
	{
		g_last_status = WEXITSTATUS(status);
		if (g_last_status == 0)
			return (0);
		return (1);
	}
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			ft_printerror("\n");
		g_last_status = signal + 128;
		return (1);
	}
	return (0);
}

static void	handle_termsig_display(t_sh *sh, size_t cmd_index, int signal)
{
	if (signal == SIGSEGV)
		ft_printerror("Segmentation fault (core dumped)\n");
	else if (signal == SIGBUS)
		ft_printerror("Bus error (core dumped)\n");
	else if (signal == SIGINT)
		ft_printerror("\n");
	else if (signal == SIGQUIT)
	{
		if (cmd_index == sh->cmd_nb - 1 || sh->cmd_nb == 1)
			ft_printerror("Quit (core dumped)\n");
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
	{
		if (cmd_index == sh->cmd_nb - 1|| sh->cmd_nb == 1)
			g_last_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		handle_termsig_display(sh, cmd_index, signal);
		if (cmd_index == sh->cmd_nb - 1|| sh->cmd_nb == 1)
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
