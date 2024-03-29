/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:52 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/14 23:33:57 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "exec.h"

static void	update_env(t_sh *sh, t_list **env)
{
	char	*cwd;
	char	*tmp;

	cwd = var_value("PWD", 3, *env);
	if (!cwd)
		cwd = ft_strdup("");
	tmp = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	do_export(env, tmp);
	free(tmp);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		tmp = ft_strjoin("PWD=", cwd);
		do_export(env, tmp);
		ft_replacefree((void **)&sh->cwd, cwd);
		free(tmp);
	}
	else
		errno = 1;
}

static int	cd_home(t_sh *sh)
{
	char	*home;

	home = var_value("HOME", 4, sh->env);
	if (!home)
	{
		ft_printerror("minish: cd: HOME not set\n");
		return (1);
	}
	if (!chdir(home))
		update_env(sh, &sh->env);
	free(home);
	return (0);
}

static char	*build_curpath(t_sh *sh, t_cmd *cmd)
{
	int			i;
	char		*path;
	char		**cdpath;
	struct stat	mode;

	i = -1;
	path = var_value("CDPATH", 6, sh->env);
	if (!path)
		return (NULL);
	cdpath = ft_split(path, ':');
	free(path);
	while (cdpath && cdpath[++i])
	{
		path = join_path(cdpath[i], cmd->args[1]);
		if (!path || (stat(path, &mode) == 0 && S_ISDIR(mode.st_mode)
				&& !access(path, X_OK)))
		{
			ft_putendl_fd(path, cmd->redir_out.fd);
			break ;
		}
		ft_strdel(&path);
	}
	ft_strarrayclear(&cdpath);
	return (path);
}

static char	*get_curpath(t_sh *sh, t_cmd *cmd)
{
	if (ft_strchr(cmd->args[1], '/') || ft_strchr(cmd->args[1], '.'))
		return (ft_strdup(cmd->args[1]));
	return (build_curpath(sh, cmd));
}

int	mini_cd(t_sh *sh, t_cmd *cmd)
{
	char	*path;

	if (!cmd->args[1])
		return (cd_home(sh));
	if (cmd->args[2])
	{
		error_display("cd", "too many arguments", 0);
		return (1);
	}
	path = get_curpath(sh, cmd);
	if (!path)
		path = ft_strdup(cmd->args[1]);
	if (chdir(path) < 0)
	{
		if (errno == ESTALE)
			errno = ENOENT;
		ft_printerror("minish: cd: %s: %s\n", cmd->args[1], strerror(errno));
	}
	else
		update_env(sh, &sh->env);
	free(path);
	return (errno != 0);
}
