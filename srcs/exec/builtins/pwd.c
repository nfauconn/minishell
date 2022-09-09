/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:51:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/09 19:28:50 by nfauconn         ###   ########.fr       */
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

	(void)sh;
	(void)cmd;
	name = getcwd(NULL, 0);
	if (!name)
	{
		error_display("pwd", strerror(errno), 0);
		return (errno);
	}
	ft_putendl_fd(name, cmd->redir_out.fd);
	free(name);
	return (0);
}
