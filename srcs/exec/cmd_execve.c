/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:56:04 by user42            #+#    #+#             */
/*   Updated: 2022/07/29 03:51:52 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"

void	cmd_execve(t_sh *sh, t_cmd *cmd)
{
	struct stat		mode;
	int				error;

	error = 0;
	if (!*(cmd->name))
	{
		error_display("\'\'", "command not found", 0);
		error = -1;
	}
	cmd->env = get_env_tab(sh->env);
	cmd->env_paths = get_path_tab(sh->env);
	if (!cmd->env_paths || ft_strlen(var_value("PATH", 4, sh->env)) == 0)
	{
		error_display(cmd->name, "No such file or directory", 0);
		exit(127);
	}
	if (is_absolute_path(cmd->name))
	{
		if (stat(cmd->name, &mode) == 0 && S_ISDIR(mode.st_mode))
		{
			error_display(cmd->name, "Is a directory", 0);
			exit(1);
		}
		execve(cmd->name, cmd->args, cmd->env_paths);
		error_display(cmd->name, strerror(errno), 0);
		exit(127);
	}
	execve(cmd->name, cmd->args, cmd->env_paths);
	if (errno == EACCES)
	{
		error_display(cmd->name, strerror(errno), 0);
		exit (126);
	}
	error_display(cmd->name, "command not found", 0);
	exit(127);
}

/*
	if (is_absolute_path(cmd->name))
	{
		if (access(cmd->name, F_OK) == SUCCESS)
		{
			if (access(cmd->name, X_OK) < 0)
			{
				error_display(cmd->name, "permission denied", 0);
				exit(NOT_EXECUTABLE);
			}
			if (stat(cmd->name, &mode) == 0 && S_ISDIR(mode.st_mode))
			{
				error_display(cmd->name, "Is a directory", 0);
				exit(IS_DIR);
			}
			execve(cmd->name, cmd->args, cmd->env_paths);
		}
		else
		{
			error_display(cmd->name, "No such file or directory", 0);
			exit(NO_SUCH_FILE);
		}
	}
*/



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