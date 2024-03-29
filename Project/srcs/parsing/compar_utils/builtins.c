/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 23:52:53 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/16 09:00:04 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	is_builtin(char *cmd_name)
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
