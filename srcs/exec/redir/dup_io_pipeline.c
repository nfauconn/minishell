/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_io_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:29:41 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/20 16:43:57 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static void	dup_output(t_cmd *cmd, int p[2])
{
	if (cmd->redir_out.fd != STDOUT_FILENO && cmd->redir_out.fd != NO_REDIR)
	{
		dup2(cmd->redir_out.fd, STDOUT_FILENO);
		close(cmd->redir_out.fd);
	}
	else if (cmd->next)
		dup2(p[1], STDOUT_FILENO);
	close(p[1]);
}

static void	dup_input(t_cmd *cmd, int fd_in)
{
	if (cmd->redir_in.fd != STDIN_FILENO && cmd->redir_in.fd != NO_REDIR)
	{
		dup2(cmd->redir_in.fd, STDIN_FILENO);
		close(cmd->redir_in.fd);
	}
	else
		dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

t_bool	dup_io_pipeline(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	t_bool	error;

	error = open_redir(cmd);
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (error)
	{
		ft_printerror("error\n");
		close(p[1]);
		exit_clear_child(sh, error);
	}
	dup_input(cmd, fd_in);
	dup_output(cmd, p);
	return (0);
}
