/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:51 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/10 14:47:22 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	run_heredoc(int *fd, char *delim)
{
	char	*line;

	*fd = open("/tmp/.here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*fd < 0)
		return ;
	line = readline("heredoc> ");
	//printf("readline: %s\n", line);
	while (line && (line[0] == '\n' || ft_strcmp(line, delim)))
	{
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
		if (!line)
			break ;
	}
	free(line);
	close(*fd);
	*fd = open("/tmp/.here_doc", O_RDONLY);
	if (*fd < 0)
	{
		ft_printerror("minish: here_doc: %s\n", strerror(errno));
	}
}
*/
void	cmd_redirections(t_cmd *cmd, t_list *token)
{
	cmd->redir[0] = -1;
	cmd->redir[1] = -1;
	errno = 0;
	while (token && !is_separator(token->type) && !errno)
	{
		if (is_in_redir_path(token->type))
		{
			if (cmd->redir[0] >= 0)
				close(cmd->redir[0]);
			if (token->type == INFILE_PATH)
				cmd->redir[0] = open((char *)token->content, O_RDONLY);
			else if (token->type == HEREDOC)
			{
				/*DONT WORK AAAAAAAAAAAAAAH*/
				//run_heredoc(&cmd->redir[0], token->content);
			}
		}
		else if (is_out_redir_path(token->type))
		{
			if (cmd->redir[1] >= 0)
				close(cmd->redir[1]);
			if (token->type == APPEND_OUTFILE_PATH)
				cmd->redir[1] = open((char *)token->content, O_CREAT | O_APPEND | O_WRONLY, 0644);
			else if (token->type == TRUNC_OUTFILE_PATH)
				cmd->redir[1] = open((char *)token->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		if (errno)
		{
			ft_printerror("minish: %s: %s\n", (char *)token->content, strerror(errno));
		}
		token = token->next;
	}
}
