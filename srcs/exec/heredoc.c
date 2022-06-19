/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/06/19 13:16:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	run_heredoc(int *fd, char *delim)
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
