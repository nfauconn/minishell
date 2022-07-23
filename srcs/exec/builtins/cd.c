/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:52 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/23 00:18:26 by mdankou          ###   ########.fr       */
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

	args = cmd->args;
	if (!args[1])
		errno = EINVAL;
	else if (args[2])
		errno = 1;
	else
	{
		if (!chdir(args[1]))
		{
			update_env(&sh->env);
		}
	}
	if (errno == 1)
		ft_printerror("minish: cd: too many arguments\n");
	else if (errno)
		ft_printerror("minish: cd: %s: %s\n", args[1], strerror(errno));
	return (errno != 0);
}
