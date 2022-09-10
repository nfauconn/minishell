/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:51:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 15:48:07 by mdankou          ###   ########.fr       */
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
	char	*name;

	(void)sh;
	(void)cmd;
	name = getcwd(NULL, 0);
	if (!name)
	{
		error_display("pwd", strerror(errno), 0);
		return (errno);
	}
	handle_redirection(sh, cmd);
	ft_putendl_fd(name, cmd->redir_out.fd);
	free(name);
	return (0);
}
