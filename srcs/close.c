/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:42:38 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 00:44:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "close.h"

void	close_if_no_std(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
}

void	close_cmd_redirs(t_cmd *cmd)
{
	close_if_no_std(cmd->redir_in);
	if (cmd->heredoc_infile)
		unlink(cmd->infile_name);
	close_if_no_std(cmd->redir_out);	
}
