/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/06/20 18:17:53 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
static void	sigTerm(int sig_num) A UTILISER POUR METTRE NL APRES SINGINT
{
	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(139);
	}
}
*/

void	run_heredoc(int *fd, char *delim)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal_catching_mode(PGM_EXEC);
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
	signal(SIGINT, SIG_IGN);
	wait(NULL);
	signal_catching_mode(INTERACTIVE);
	/*
	write(1, "\n", 1);
	rl_redisplay();
	*/
}
