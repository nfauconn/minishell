/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:29:45 by user42            #+#    #+#             */
/*   Updated: 2022/07/08 15:19:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

void	redir_apply(t_cmd *cmd, int p[2], int fd_in)
{
	if (cmd->redir_in == REDIR_FAIL || cmd->redir_out == REDIR_FAIL)
	{
		close(p[1]);
		exit(WRONG_REDIR);
	}
	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	else if (fd_in)
		dup2_close_old(fd_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
	else if (cmd->next)
	{
		#ifdef DEBUG
		ft_printerror ("dup2           : %d becomes %d\n", p[1], STDOUT_FILENO);
		#endif
		dup2(p[1], STDOUT_FILENO);
	}
	close(p[1]);
}
