/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:07:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/20 16:50:01 by nfauconn         ###   ########.fr       */
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
	sh->last_exit_code = status;
	return (status);
}
