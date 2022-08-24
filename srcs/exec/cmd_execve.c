/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:56:04 by user42            #+#    #+#             */
/*   Updated: 2022/08/20 17:56:14 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parse.h"

static uint8_t	exec_absolute_path(char **args, char **envp)
{
	struct stat		mode;
	uint8_t			error;

	if (!ft_strcmp(args[0], ".")
		|| (stat(args[0], &mode) == 0 && S_ISDIR(mode.st_mode)))
		error = 1;
	else
	{
		execve(args[0], args, envp);
		error = errno;
	}
	if (error == 1)
		error_display(args[0], "Is a directory", 0);
	else
		error_display(args[0], strerror(error), 0);
	return (error);
}

static uint8_t	try_exec(char **paths, char **args, char **envp, size_t i)
{
	char		*path;
	uint8_t		error;

	path = join_path(paths[i], args[0]);
	ft_strarrayclear(&paths);
	execve(path, args, envp);
	error = errno;
	ft_strdel(&path);
	return (error);
}

static uint8_t	try_possible_paths(char **args, char **envp)
{
	uint8_t		error;
	size_t		i;
	t_bool		all_paths_tried;
	char		**possible_paths;

	i = 0;
	errno = 0;
	error = 0;
	all_paths_tried = 0;
	while (!all_paths_tried)
	{
		possible_paths = get_path_tab(envp);
		if (possible_paths[i])
		{
			error = try_exec(possible_paths, args, envp, i);
			i++;
		}
		else
		{
			all_paths_tried = 1;
			ft_strarrayclear(&possible_paths);
		}
	}
	return (error);
}

static uint8_t	exec_relative_path(char **args, char **envp)
{
	uint8_t		error;

	if (no_path_in_env(envp))
	{
		error = 127;
		error_display(args[0], "No such file or directory", 0);
	}
	else
	{
		error = try_possible_paths(args, envp);
		if (error != ENOENT)
			error_display(args[0], strerror(error), 0);
		else
		{
			error = 127;
			error_display(args[0], "command not found", 0);
		}
	}
	return (error);
}

void	cmd_execve(t_sh *sh, t_cmd *cmd)
{
	char	**args;
	char	**envp;
	uint8_t	exit_code;

	if (!*(cmd->args[0]))
		perror_exit_clear(sh, "\'\'", "command not found", 127);
	args = ft_strarraydup(cmd->args);
	envp = get_env_tab(sh->env);
	clear_sh(sh);
	if (is_absolute_path(args[0]))
		exit_code = exec_absolute_path(args, envp);
	else
		exit_code = exec_relative_path(args, envp);
	ft_strarrayclear(&args);
	ft_strarrayclear(&envp);
	exit(exit_code);
}
