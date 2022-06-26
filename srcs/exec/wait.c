/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:07:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/26 23:02:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_children(t_sh *sh)
{
	pid_t	pid;
	int		status;
	size_t	i;

	i = 1;
	while (i <= sh->cmd_nb)
	{
		pid = waitpid(-1, &status, WUNTRACED);
		if (WIFEXITED(status) && status == 139)
			ft_printerror("segfault\n");
		i++;
	}
	return (status);
}

/* 		if (WIFEXITED(status) && status == NOT_FOUND)
			sh->last_exit_code = status; */