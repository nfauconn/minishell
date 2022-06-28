/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:07:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/28 19:33:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_status(t_sh *sh, int status)
{
	sh->last_status = status;
}

int	wait_children(t_sh *sh)
{
	pid_t	pid;
	int		status;
	int		signal;
	size_t	i;

	i = 0;
	while (i < sh->cmd_nb)
	{
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
		i++;
	}
	return (status);
}

/* 		if (WIFEXITED(status) && status == NOT_FOUND)
			sh->last_status = status; */