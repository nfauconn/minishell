/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:52 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/05 01:23:33 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_cd(t_sh *sh, t_cmd *cmd)
{
	DIR		*dir;

	(void)sh;
	char **args = cmd->args;
	if (!args[1])
		errno = EINVAL;
	else if (args[2])
		errno = E2BIG;
	else
	{
		dir = opendir(args[1]);
		if (!dir)
			error_display("cd", strerror(errno));
		else
			chdir(args[1]);
	}
	return (errno);
}
