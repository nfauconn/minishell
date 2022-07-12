/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/12 19:23:05 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	mini_env(t_sh *sh, t_cmd *cmd)
{
	t_list	*l;

	(void)cmd;
	l = sh->env;
	if (cmd->redir_out == REDIR_FAIL)
		return (WRONG_REDIR);
	if (cmd->redir_out == NO_REDIR)
		cmd->redir_out = STDIN_FILENO;
	while (l)
	{
		ft_printf("%s\n", (char *)l->content);
		l = l->next;
	}
	return (0);
}
