/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/24 00:48:16 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	mini_env(t_sh *sh, t_cmd *cmd)
{
	t_list	*l;

	if (cmd->args[1])
	{
		error_display("env", "does not handle arguments", 0);
		return (1);
	}
	l = sh->env;
	while (l)
	{
		ft_printf("%s\n", (char *)l->content);
		l = l->next;
	}
	return (0);
}
