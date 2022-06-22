/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/06/22 17:12:29 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	sigTerm(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		exit(128 + SIGINT);
	}
}

void	run_heredoc(int *fd, char *delim)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigTerm);
		*fd = open("/tmp/.here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*fd < 0)
			return ;
		line = readline("> ");
		if (!line)
		{
			write(1, "\n", 1);
			return ;
		}
		while (line && (line[0] == '\n' || ft_strcmp(line, delim)))
		{
			write(*fd, line, ft_strlen(line));
			write(*fd, "\n", 1);
			free(line);
			line = readline("> ");
			if (!line)
			{
				write(1, "\n", 1);
				break;
			}
		}
		free(line);
		close(*fd);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	wait(NULL);
	signal_catching_mode(INTERACTIVE);
	*fd = open("/tmp/.here_doc", O_RDONLY);
	if (*fd < 0)
	{
		ft_printerror("minish: here_doc: %s\n", strerror(errno));
	}
}
