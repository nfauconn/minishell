/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:07:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/21 22:09:48 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_last_status(t_sh *sh, int status)
{
	sh->last_status = status;
}

void	wait_heredoc(t_sh *sh)
{
	pid_t	pid;
	int		status;
	int		signal;

	pid = waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			ft_printerror("\n");
		set_last_status(sh, signal + 128);
	}
	else if (WIFEXITED(status))
	{
		set_last_status(sh, WEXITSTATUS(status));
	}
}

void	wait_child(t_sh *sh)
{
	pid_t	pid;
	int		status;
	int		signal;

	pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		set_last_status(sh, WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGSEGV)
			ft_printerror("Segmentation fault (core dumped)\n");
		else if (signal == SIGBUS)
			ft_printerror("Bus error (core dumped)\n");
		else if (signal == SIGINT)
			ft_printerror("\n");
		set_last_status(sh, signal + 128);
	}
}

void	wait_children(t_sh *sh)
{
	size_t	i;

	i = 0;
	while (i < sh->cmd_nb)
	{
		wait_child(sh);
		i++;
	}
}
