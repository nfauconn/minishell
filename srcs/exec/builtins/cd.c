/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:52 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/22 23:08:13 by nfauconn         ###   ########.fr       */
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
	free(cwd);
}

int	mini_cd(t_sh *sh, t_cmd *cmd)
{
	char	**args;

	args = cmd->args;
	if (!args[1])
		errno = EINVAL;
	else if (args[2])
		errno = E2BIG;
	else
	{
		if (!chdir(args[1]))
			update_env(&sh->env);
		else
		{
			ft_printerror("minish: cd: %s: \
				No such file or directory\n", args[1]);
			return (1);
		}
	}
	if (errno)
	{
		ft_printerror("minish: cd: %s: %s\n", args[1], strerror(errno));
		return (1);
	}
	return (0);
}
