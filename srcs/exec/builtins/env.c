/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/18 15:41:03 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	mini_env(t_sh *sh, t_cmd *cmd)
{
	t_list	*l;

	if (cmd->args_tab[1])
	{
		ft_printerror("minish: env: does not handle arguments\n");
		return (1);
	}
	l = sh->env;
	if (cmd->redir_error)
		return (1);
	if (cmd->redir_out.fd == NO_REDIR)
		cmd->redir_out.fd = STDIN_FILENO;
	while (l)
	{
		if (ft_strchr((char *)l->content, '='))
			ft_printf("%s\n", (char *)l->content);
		l = l->next;
	}
	return (0);
}
