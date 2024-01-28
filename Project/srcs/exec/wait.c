/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:07:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/07 16:28:22 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern uint8_t	g_last_status;

static void	handle_termsig_display(int signal)
{
	if (signal == SIGSEGV)
		ft_printerror("Segmentation fault (core dumped)\n");
	else if (signal == SIGBUS)
		ft_printerror("Bus error (core dumped)\n");
	else if (signal == SIGINT)
		ft_printerror("\n");
	else if (signal == SIGQUIT)
		ft_printerror("Quit (core dumped)\n");
}

void	wait_child(t_sh *sh, pid_t last_cmd_pid)
{
	pid_t	pid;
	int		status;
	int		signal;

	pid = wait(&status);
	if (pid < 0)
	{
		error_display("waitpid", strerror(errno), 0);
		exit_clear_minish(sh, EXIT_FAILURE);
	}
	if (pid == last_cmd_pid)
	{
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			handle_termsig_display(signal);
			g_last_status = signal + 128;
		}
	}
}

void	wait_children(t_sh *sh, pid_t last_cmd_pid)
{
	size_t	i;

	i = 0;
	while (i < sh->cmd_nb)
	{
		wait_child(sh, last_cmd_pid);
		i++;
	}
}
