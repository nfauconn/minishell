/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:51:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 19:04:11 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
*	pwd with no options (and no arguments)
*	@return 0 Successful completion. >0 An error occurred.
*/

int	mini_pwd(t_sh *sh, t_cmd *cmd)
{
	char	*name;
	int		fd_out;

	(void)sh;
	(void)cmd;
	name = getcwd(NULL, 0);
	if (!name)
	{
		error_display("pwd", strerror(errno), 0);
		return (errno);
	}
	if (sh->cmd_nb == 1 && cmd->redir_out)
		fd_out = handle_redir_out(cmd);
	else
		fd_out = STDOUT_FILENO;
	ft_putendl_fd(name, fd_out);
	free(name);
	return (0);
}
