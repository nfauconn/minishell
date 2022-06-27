/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/06/27 15:28:23 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//DOIT AJOUTER LE EXPAND 

static void	read_heredoc_nbline(int *nb)
{
	int	fd;

	fd = open("/tmp/.here_doc2", O_RDONLY);
	if (fd < 0)
		return ;
	read(fd, nb, sizeof(int));
}

static void	write_heredoc_nbline(int nb)
{
	int	fd;

	fd = open("/tmp/.here_doc2", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return ;
	write(fd, &nb, sizeof(int));
}

static void	heredoc_job(int *fd, char *delim)
{
	int		nbltotal;
	int		nbl;
	char	*line;

	signal(SIGINT, SIG_DFL);
	nbl = 0;
	nbltotal = 1;
	read_heredoc_nbline(&nbltotal);
	*fd = open("/tmp/.here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*fd < 0)
		exit(-1);
	line = readline("> ");
	while (++nbl && line && (line[0] == '\n' || ft_strcmp(line, delim)))
	{
		ft_putendl_fd(line, *fd);
		free(line);
		line = readline("> ");
	}
	if (!line)
		ft_printerror("bash: warning: here-document"\
		" at line %d delimited by end-of-file (wanted `%s')\n", nbltotal, delim);
	write_heredoc_nbline(nbltotal += nbl);
	free(line);
	close(*fd);
	exit(0);
}

void	run_heredoc(t_sh *sh, int *fd, char *delim)
{
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid == 0)
	{
		heredoc_job(fd, delim);
	}
	signal(SIGINT, SIG_IGN);
	wait(&wstatus);
	signal_catching_mode(INTERACTIVE);
	if (wstatus != 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	*fd = open("/tmp/.here_doc", O_RDONLY);
	if (*fd < 0)
	{
		ft_printerror("minish: here_doc: %s\n", strerror(errno));
	}
}
