/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:56:04 by user42            #+#    #+#             */
/*   Updated: 2022/07/08 14:43:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	cmd_execve(t_sh *sh, t_cmd *cmd)
{
	cmd->env = get_env_tab(sh->env);
	if (access(cmd->name, X_OK) != -1)
		execve(cmd->name, cmd->args, cmd->env);
	cmd->env_paths = get_path_tab(sh->env);
	if (!cmd->env_paths || !find_path(cmd, cmd->env_paths))
		error_exit(cmd->name, NOT_FOUND);
	else
	{
		execve(cmd->path, cmd->args, cmd->env);
		error_exit(cmd->name, NOT_EXECUTABLE);
	}
	error_exit(cmd->name, 1);
}
