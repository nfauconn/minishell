/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:07:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/22 15:27:09 by nfauconn         ###   ########.fr       */
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
/* 		if (WIFEXITED(status) && status == NOT_FOUND)
			sh->last_exit_code = status; */
		i++;
	}
	return (status);
}
