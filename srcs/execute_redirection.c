/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:51 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/08 18:32:02 by mdankou          ###   ########.fr       */
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
void	apply_redirections(t_list *token)
{
	int		redir[2];

	errno = 0;
	while (token && !errno)
	{
		if (token->type == IN_REDIR || token->type == HEREDOC)
			close(redir[0]);
		else if (token->type == OUT_REDIR)
			close(redir[1]);
		errno = 0;
		if (token->type == IN_REDIR)
		{
			if (token->next)
				redir[0] = open((char *)token->next->content, O_RDONLY);
		}
		else if (token->type == OUT_REDIR)
		{
			if (token->next)
				redir[1] = open((char *)token->next->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		else if (token->type == HEREDOC)
		{
			/*DONT WORK AAAAAAAAAAAAAAH*/
			//run_heredoc(&redir[0], token->next->content);
		}
		token = token->next;
	}
	if (errno)
	{
		ft_printerror("minish: %s: %s\n", (char *)token->content, strerror(errno));
	}
}
