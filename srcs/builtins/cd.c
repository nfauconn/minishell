/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:52 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/05 22:23:23 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_value(char *str, size_t len, t_list *env);
void	do_export(t_list **env, char *assign);

int	mini_cd(t_sh *sh, t_cmd *cmd)
{
	char	*cwd;
	char	*tmp;

	char **args = cmd->args;
	if (!args[1])
		errno = EINVAL;
	else if (args[2])
		errno = E2BIG;
	else
	{
		if (!chdir(args[1]))
		{
			tmp = ft_strjoin("OLDPWD=", var_value("PWD", 3, sh->env));
			do_export(&sh->env, tmp);
			free(tmp);
			cwd = getcwd(NULL, 0);
			if (cwd)
			{
				tmp = ft_strjoin("PWD=", cwd);
				do_export(&sh->env, tmp);
				free(tmp);
			}
			free(cwd);
		}
	}
	if (errno == 2)
		ft_printerror("minish: cd: %s: %s\n", args[1], strerror(errno));
	else if (errno)
		ft_printerror("minish: cd: %s\n", strerror(errno));
	return (errno);
}
