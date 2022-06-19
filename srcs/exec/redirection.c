/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:20:37 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/19 13:04:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_redirections(t_cmd *cmd, t_list *token)
{
	errno = 0;
	cmd->redir[0] = FILE_NOT_USED;
	cmd->redir[1] = FILE_NOT_USED;
	while (token && !is_separator(token->type) && !errno)
	{
		if (is_in_redir_path(token->type))
		{
			if (cmd->redir[0] > STDERR_FILENO)
				close(cmd->redir[0]);
			if (token->type == INFILE_PATH)
				cmd->redir[0] = open((char *)token->content, O_RDONLY);
			else
				run_heredoc(&cmd->redir[0], token->content);
		}
		else if (is_out_redir_path(token->type))
		{
			if (cmd->redir[1] > STDERR_FILENO)
				close(cmd->redir[1]);
			if (token->type == APPEND_OUTFILE_PATH)
				cmd->redir[1] = open((char *)token->content, O_CREAT | O_APPEND | O_WRONLY, 0644);
			else if (token->type == TRUNC_OUTFILE_PATH)
				cmd->redir[1] = open((char *)token->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		if (errno)
			ft_printerror("minish: %s: %s\n", (char *)token->content, strerror(errno));
		token = token->next;
	}
}
