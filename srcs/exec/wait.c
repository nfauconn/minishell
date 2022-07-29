/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:07:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/29 00:53:31 by nfauconn         ###   ########.fr       */
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
		g_last_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		g_last_status = signal + 128;
	}
}

void	wait_child(void)
{
	pid_t	pid;
	int		status;
	int		signal;

	pid = waitpid(-1, &status, 0);
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
			ft_printerror("Quit (core dumped)\n");
		g_last_status = signal + 128;
	}
}

void	wait_children(t_sh *sh)
{
	size_t	i;

	i = 0;
	while (i < sh->cmd_nb)
	{
		wait_child();
		i++;
	}
}

//c est le parent qui affiche le retour a la ligne ou le quit
//quit core dump s affiche seulement si
// c est le dernier enfant attendu qui recoit un SIGQUIT