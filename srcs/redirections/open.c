/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:19:59 by user42            #+#    #+#             */
/*   Updated: 2022/07/29 01:31:54 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static int	open_redir_out(t_cmd *cmd)
{
	if (cmd->redir_out_type == APPEND_OUTFILE_NAME)
		cmd->redir_out = open(cmd->outfile_name, \
			O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		cmd->redir_out = open(cmd->outfile_name, \
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (cmd->redir_out < 0)
	{
		error_display(cmd->outfile_name, strerror(errno), 0);
		return (1);
	}
	ft_printerror("cmd->redir_out = %d\n", cmd->redir_out);
	return (0);
}

static int	open_redir_in(t_cmd *cmd)
{
	cmd->redir_in = open(cmd->infile_name, O_RDONLY);
	if (cmd->redir_in < 0)
	{
		error_display(cmd->infile_name, strerror(errno), 0);
		return (1);
	}
	return (0);
}

int	open_redir(t_cmd *cmd)
{
	errno = 0;
	cmd->redir_in = NO_REDIR;
	cmd->redir_out = NO_REDIR;
	if (cmd->access_error)
		return (1);
	if (cmd->infile_name && open_redir_in(cmd) == FAILURE)
		return (1);
	if (cmd->outfile_name && open_redir_out(cmd) == FAILURE)
		return (1);
	return (0);
}
