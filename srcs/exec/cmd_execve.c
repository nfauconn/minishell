/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:56:04 by user42            #+#    #+#             */
/*   Updated: 2022/07/29 03:57:50 by nfauconn         ###   ########.fr       */
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
		execve(cmd->name, cmd->args, cmd->env);
		error_display(cmd->name, strerror(errno), 0);
		exit(127);
	}
	execve(cmd->name, cmd->args, cmd->env);
	if (errno == EACCES)
	{
		error_display(cmd->name, strerror(errno), 0);
		exit (126);
	}
	error_display(cmd->name, "command not found", 0);
	exit(127);
}
