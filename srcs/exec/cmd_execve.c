/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:56:04 by user42            #+#    #+#             */
/*   Updated: 2022/08/19 02:24:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parse.h"

static int	no_path_in_env(t_sh *sh, t_cmd *cmd)
{
	int		ret;
	char	*path_val;

	path_val = var_value("PATH", 4, sh->env);
	if (!cmd->possible_paths || !path_val || ft_strlen(path_val) == 0)
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

static void	exec_absolute_path(t_sh *sh, t_cmd *cmd)
{
	if (cmd_is_dir(cmd->name))
		perror_exit(sh, cmd->name, "Is a directory", 1);
	execve(cmd->name, cmd->args, cmd->envp);
	perror_exit(sh, cmd->name, strerror(errno), 127);
}

void	cmd_execve(t_sh *sh, t_cmd *cmd)
{
	size_t	i;

	if (!*(cmd->name))
		perror_exit(sh, "\'\'", "command not found", 127);
	cmd->possible_paths = get_path_tab(sh->env);
	cmd->envp = get_env_tab(sh->env);
	if (no_path_in_env(sh, cmd))
		perror_exit(sh, cmd->name, "No such file or directory", 127);
	if (is_absolute_path(cmd->name))
		exec_absolute_path(sh, cmd);
	i = 0;
	errno = 0;
	while (cmd->possible_paths[i])
	{
		cmd->path = join_path(cmd->possible_paths[i], cmd->name);
//		clear_before_exec(sh);
		execve(cmd->path, cmd->args, cmd->envp);
		i++;
		ft_strdel(&cmd->path);
	}
	if (errno != ENOENT)
		perror_exit(sh, cmd->name, strerror(errno), 126);
	perror_exit(sh, cmd->name, "command not found", 127);
}
