/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:51:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/14 16:14:28 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
*	pwd with no options (and no arguments)
*	@return 0 Successful completion. >0 An error occurred.
*/

static void	handle_redirection(t_sh *sh, t_cmd *cmd)
{
	if (sh->cmd_nb > 1)
	{
		cmd->redir_in.fd = STDIN_FILENO;
		cmd->redir_out.fd = STDOUT_FILENO;
	}
}

int	mini_pwd(t_sh *sh, t_cmd *cmd)
{
	(void)sh;
	(void)cmd;
	handle_redirection(sh, cmd);
	ft_putendl_fd(sh->cwd, cmd->redir_out.fd);
	return (0);
}
