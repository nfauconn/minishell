/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:19:59 by user42            #+#    #+#             */
/*   Updated: 2022/08/16 09:00:04 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static t_bool	open_redir_out(t_cmd *cmd)
{
	if (cmd->redir_out.is_append)
		cmd->redir_out.fd = open(cmd->redir_out.filename, \
			O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		cmd->redir_out.fd = open(cmd->redir_out.filename, \
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (cmd->redir_out.fd < 0)
	{
		error_display(cmd->redir_out.filename, strerror(errno), 0);
		return (1);
	}
	return (0);
}

static t_bool	open_redir_in(t_cmd *cmd)
{
	cmd->redir_in.fd = open(cmd->redir_in.filename, O_RDONLY);
	if (cmd->redir_in.fd < 0)
	{
		error_display(cmd->redir_in.filename, strerror(errno), 0);
		return (1);
	}
	return (0);
}

t_bool	open_redir(t_cmd *cmd)
{
	cmd->redir_in.fd = NO_REDIR;
	cmd->redir_out.fd = NO_REDIR;
	if (cmd->redir_error)
		return (1);
	if (cmd->redir_in.filename && open_redir_in(cmd) == FAIL)
		return (1);
	if (cmd->redir_out.filename && open_redir_out(cmd) == FAIL)
		return (1);
	return (0);
}
