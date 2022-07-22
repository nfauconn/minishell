/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:56:04 by user42            #+#    #+#             */
/*   Updated: 2022/07/23 00:12:21 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	cmd_execve(t_sh *sh, t_cmd *cmd)
{
	if (!*(cmd->name))
		error_exit(cmd->name, NOT_FOUND);
	cmd->env = get_env_tab(sh->env);
	if (access(cmd->name, X_OK) != -1)
		execve(cmd->name, cmd->args, cmd->env);
	cmd->env_paths = get_path_tab(sh->env);
	if (!cmd->env_paths || !find_path(cmd, cmd->env_paths))
	{
		if (is_relative_path(cmd->name))
			error_exit(cmd->name, NOT_FOUND);
		else
			error_exit(cmd->name, NO_SUCH_FILE);
	}
	else
	{
		execve(cmd->path, cmd->args, cmd->env);
		error_exit(cmd->name, NOT_EXECUTABLE);
	}
	error_exit(cmd->name, 1);
}
