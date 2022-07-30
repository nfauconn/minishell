/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:56:04 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 19:38:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"

static void	perror_exit(t_sh *sh, char *s1, char *s2, unsigned char exit_code)
{
	error_display(s1, s2, 0);
	exit_clear_child(sh, exit_code);
}

static int	no_path_in_env(t_sh *sh, t_cmd *cmd)
{
	if (!cmd->possible_paths || ft_strlen(var_value("PATH", 4, sh->env)) == 0)
		return (1);
	return (0);
}

static int	cmd_is_dir(char *cmd_name)
{
	struct stat		mode;

	if (stat(cmd_name, &mode) == 0 && S_ISDIR(mode.st_mode))
		return (1);
	return (0);
}

void	cmd_execve(t_sh *sh, t_cmd *cmd)
{
	if (!*(cmd->name))
		perror_exit(sh, "\'\'", "command not found", 127);
	cmd->possible_paths = get_path_tab(sh->env);
	if (no_path_in_env(sh, cmd))
		perror_exit(sh, cmd->name, "No such file or directory", 127);
	if (is_absolute_path(cmd->name))
	{
		if (cmd_is_dir(cmd->name))
			perror_exit(sh, cmd->name, "Is a directory", 1);
		execve(cmd->name, cmd->args, cmd->possible_paths);
		perror_exit(sh, cmd->name, strerror(errno), 127);
	}
	if (find_path(cmd, cmd->possible_paths))
	{
		execve(cmd->path, cmd->args, cmd->possible_paths);
		if (errno == EACCES)
			perror_exit(sh, cmd->name, strerror(errno), 126);
	}
	perror_exit(sh, cmd->name, "command not found", 127);
}
