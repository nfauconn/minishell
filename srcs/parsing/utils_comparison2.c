/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_comparison2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:56:44 by user42            #+#    #+#             */
/*   Updated: 2022/07/22 22:33:01 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_metacharacter(int c)
{
	return (is_blank(c) || is_rediroperator(c) || is_sep(c));
}

int	is_builtin(char *cmd_name)
{
	int			i;
	static char	*builtins[8] = {"cd", "echo", "env", "exit", "export", \
	"pwd", "unset", 0};

	if (!cmd_name || !*cmd_name)
		return (-1);
	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(cmd_name, builtins[i]))
			return (i);
		i++;
	}
	return (-1);
}
