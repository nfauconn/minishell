/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:20:37 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/14 14:51:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc(int *fd, char *delim)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		*fd = open("/tmp/.here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*fd < 0)
			return ;
		line = readline("heredoc> ");
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
		exit(0);
	}
	else
		wait(NULL);
}

void	cmd_redirections(t_cmd *cmd, t_list *token)
{
	errno = 0;
	cmd->redir[0] = -42;
	cmd->redir[1] = -42;
	while (token && !is_separator(token->type) && !errno)
	{
		if (is_in_redir_path(token->type))
		{
			if (cmd->redir[0] >= 0)
				close(cmd->redir[0]);
			if (token->type == INFILE_PATH)
				cmd->redir[0] = open((char *)token->content, O_RDONLY);
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
		else if (token->type == HEREDOC)
			run_heredoc(&cmd->redir[0], token->next->content);
/* 		else
		{
			cmd->redir[0] = 0;
			cmd->redir[1] = 1;
		} */
		if (errno)
			ft_printerror("minish: %s: %s\n", (char *)token->content, strerror(errno));
		token = token->next;
	}
}
