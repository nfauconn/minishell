/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:56:04 by user42            #+#    #+#             */
/*   Updated: 2022/07/28 22:10:49 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"

void	cmd_execve(t_sh *sh, t_cmd *cmd)
{
//	struct stat	mode;

	cmd->env = get_env_tab(sh->env);
	cmd->env_paths = get_path_tab(sh->env);
	if (!*(cmd->name))
		error_exit(cmd->name, NOT_FOUND);
	if (is_absolute_path(cmd->name))
	{
		if (access(cmd->name, F_OK) == SUCCESS)
		{
			if (access(cmd->name, X_OK) < 0)
			{
				error_display(cmd->name, "permission denied", 0);
				exit(NOT_EXECUTABLE);
			}
			execve(cmd->name, cmd->args, cmd->env_paths);
		}
	}
	exit(1);//temporaire
}
/* 		if (stat(cmd->name, &mode) == 0 && S_ISDIR(mode.st_mode))
			error_exit(cmd->name, IS_DIR);
		error_exit(cmd->name, NO_SUCH_FILE); */


/* 	cmd->env = get_env_tab(sh->env);
	if (access(cmd->name, X_OK) != -1)
		execve(cmd->name, cmd->args, cmd->env);
	cmd->env_paths = get_path_tab(sh->env);
	if (!cmd->env_paths || !find_path(cmd, cmd->env_paths))
	{
		if (is_absolute_path(cmd->name))
			error_exit(cmd->name, NOT_FOUND);
		else
			error_exit(cmd->name, NO_SUCH_FILE);
	}
	else
	{
		execve(cmd->path, cmd->args, cmd->env);
		error_exit(cmd->name, NOT_EXECUTABLE);
	}
	error_exit(cmd->name, 1); */