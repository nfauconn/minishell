/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:56:04 by user42            #+#    #+#             */
/*   Updated: 2022/08/19 14:43:32 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parse.h"

static int	no_path_in_env(char **possible_paths, char **envp)
{
	int		ret;
	char	*path_val;
	t_list	*env_lst;

	env_lst = ft_strarraytolist(envp);
	path_val = var_value("PATH", 4, env_lst);
	ft_lstclear(&env_lst, free);
	if (!possible_paths || !path_val || ft_strlen(path_val) == 0)
		ret = 1;
	else
		ret = 0;
	free(path_val);
	return (ret);
}

static int	cmd_is_dir(char *cmd_name)
{
	struct stat		mode;

	if (!ft_strcmp(cmd_name, "."))
		return (1);
	if (stat(cmd_name, &mode) == 0 && S_ISDIR(mode.st_mode))
		return (1);
	return (0);
}

static void	exec_absolute_path(char **args, char **envp)
{
	unsigned char	error;

	if (cmd_is_dir(args[0]))
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
	ft_strarrayclear(&args);
	ft_strarrayclear(&envp);
	exit(error);
}

static void	try_env_paths(char **args, char **envp)
{
	unsigned char		error;
	char				**possible_paths;
	char				*path;
	size_t				i;
	t_bool				all_paths_tried;

	all_paths_tried = 0;
	possible_paths = NULL;
	if (no_path_in_env(envp, possible_paths))
		error = 127;
	else
	{
		i = 0;
		errno = 0;
		while (!all_paths_tried)
		{
			possible_paths = get_path_tab(envp);
			if (possible_paths[i])
			{
				path = join_path(possible_paths[i], args[0]);
				ft_strarrayclear(&possible_paths);
				execve(path, args, envp);
				error = errno;
				ft_strdel(&path);
				i++;
			}
			else
				all_paths_tried = 1;
		}
	}
	if (error == 127)
		error_display(args[0], "No such file or directory", 0);
	else if (error != ENOENT)
		error_display(args[0], strerror(error), 0);
	else
		error_display(args[0], "command not found", 0);
	ft_strarrayclear(&args);
	ft_strarrayclear(&possible_paths);
	ft_strarrayclear(&envp);
	exit(error);
}

void	cmd_execve(t_sh *sh, t_cmd *cmd)
{
	char	**args;
	char	**envp;

	if (!*(cmd->args[0]))
		perror_exit_clear(sh, "\'\'", "command not found", 127);
	args = ft_strarraydup(cmd->args);
	envp = get_env_tab(sh->env);
	clear_sh(sh);
	if (is_absolute_path(args[0]))
		exec_absolute_path(args, envp);
	else
		try_env_paths(args, envp);
}
