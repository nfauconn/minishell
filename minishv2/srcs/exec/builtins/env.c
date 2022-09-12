/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 18:40:25 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	mini_env(t_sh *sh, t_cmd *cmd)
{
	t_list	*l;

	if (cmd->args[1])
	{
		ft_printerror("minish: env: does not handle arguments\n");
		return (1);
	}
	l = sh->env;
	if (cmd->redir_error)
		return (1);
	while (l)
	{
		if (ft_strchr((char *)l->content, '='))
			ft_printf("%s\n", (char *)l->content);
		l = l->next;
	}
	return (0);
}
