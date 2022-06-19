/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:20:37 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/19 18:51:25 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_redirections(t_cmd *cmd, t_list *token)
{
	errno = 0;
	cmd->redir_in = FILE_NOT_USED;
	cmd->redir_out = FILE_NOT_USED;
	while (token && !is_separator(token->type) && !errno)
	{
		if (is_in_redir_path(token->type))
		{
			if (cmd->redir_in > STDERR_FILENO)
				close(cmd->redir_in);
			if (token->type == INFILE_PATH)
			{
				cmd->redir_in = open((char *)token->content, O_RDONLY);
				if (cmd->redir_in < 0)
				{
					error_display((char *)token->content, strerror(errno));
					return ;
				}
			}
			else
				run_heredoc(&cmd->redir_in, token->content);
		}
		else if (is_out_redir_path(token->type))
		{
			if (cmd->redir_out > STDERR_FILENO)
				close(cmd->redir_out);
			if (token->type == APPEND_OUTFILE_PATH)
				cmd->redir_out = open((char *)token->content, O_CREAT | O_APPEND | O_WRONLY, 0644);
			else if (token->type == TRUNC_OUTFILE_PATH)
				cmd->redir_out = open((char *)token->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		if (errno)
			ft_printerror("minish: %s: %s\n", (char *)token->content, strerror(errno));
		token = token->next;
	}
}
