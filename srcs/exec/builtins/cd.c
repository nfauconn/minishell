/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:52 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/29 02:45:01 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

static void	update_env(t_list **env)
{
	char	*cwd;
	char	*tmp;

	cwd = var_value("PWD", 3, *env);
	if (!cwd)
		cwd = "\0";
	tmp = ft_strjoin("OLDPWD=", cwd);
	do_export(env, tmp);
	free(tmp);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		tmp = ft_strjoin("PWD=", cwd);
		do_export(env, tmp);
		free(tmp);
	}
	else
	{
		ft_printerror("cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n");
		errno = 0;
	}
	free(cwd);
}

static int	cd_home(t_sh *sh, char *home)
{
	if (!home)
	{
		ft_printerror("minish: cd: HOME not set\n");
		return (1);
	}
	if (!chdir(home))
		update_env(&sh->env);
	return (0);
}

int	mini_cd(t_sh *sh, t_cmd *cmd)
{
	char	**args;
	char	*home;

	args = cmd->args;
	home = var_value("HOME", 4, sh->env);
	if (!args[1])
		return (cd_home(sh, home));
	else if (args[2])
	{
		ft_printerror("minish: cd: too many arguments\n");
		return (1);
	}
	if (chdir(args[1]) < 0)
	{
		ft_printerror("minish: cd: %s: %s\n", args[1], strerror(errno));
		return (1);
	}
	update_env(&sh->env);
	return (0);
}
