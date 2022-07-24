/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/24 14:32:39 by mdankou          ###   ########.fr       */
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
	if (cmd->redir_out == REDIR_FAIL)
		return (WRONG_REDIR);
	if (cmd->redir_out == NO_REDIR)
		cmd->redir_out = STDIN_FILENO;
	while (l)
	{
		if (ft_strchr((char *)l->content, '='))
			ft_printf("%s\n", (char *)l->content);
		l = l->next;
	}
	return (0);
}
