/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:52 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/27 15:51:06 by mdankou          ###   ########.fr       */
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

int	mini_cd(t_sh *sh, t_cmd *cmd)
{
	char	**args;
	char	*home;

	args = cmd->args;
	home = var_value("HOME", 4, sh->env);
	if (!args[1])
	{
		if (home && !chdir(home))
			update_env(&sh->env);
		else if (!home)
			errno = EINVAL;
	}
	else if (args[2])
		errno = 1;
	else if (!chdir(args[1]))
		update_env(&sh->env);
	if (!home)
		ft_printerror("minish: cd: HOME not set\n");
	else if (errno == 1)
		ft_printerror("minish: cd: too many arguments\n");
	else if (errno)
		ft_printerror("minish: cd: %s: %s\n", args[1], strerror(errno));
	return (errno != 0);
}
