/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/07/23 01:03:56 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redir.h"

static void	read_heredoc_nbline(int *nb)
{
	int	fd;

	fd = open(HEREDOC_NBL_PATH, O_RDONLY);
	if (fd < 0)
		return ;
	read(fd, nb, sizeof(int));
	close(fd);
}

static void	write_heredoc_nbline(int nb)
{
	int	fd;

	fd = open(HEREDOC_NBL_PATH, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return ;
	write(fd, &nb, sizeof(int));
	close(fd);
}

static void	heredoc_warning(int nbltotal, char *delim)
{
	read_heredoc_nbline(&nbltotal);
	ft_printerror("minish: warning: here-document"\
	" at line %d delimited by end-of-file (wanted `%s')\n", nbltotal, delim);
}

static void	heredoc_job(t_sh *sh, char *hdoc_path, char *delim, t_bool quoted)
{
	int		fd;
	int		nbltotal;
	int		nbl;
	char	*line;

	nbl = 0;
	nbltotal = 1;
	fd = open(hdoc_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		exit(errno);
	line = readline("> ");
	while (++nbl && line && (line[0] == '\n' || ft_strcmp(line, delim)))
	{
		if (!quoted)
			ft_replace_free_old((void **)&line, expand_string(line, sh));
		ft_putendl_fd(line, fd);
		ft_replace_free_old((void **)&line, readline("> "));
	}
	if (!line)
		heredoc_warning(nbltotal, delim);
	write_heredoc_nbline(nbltotal += nbl);
	free(line);
	close(fd);
	exit(0);
}

void	run_heredoc(t_sh *sh, char *hdoc_path, char *delim, t_bool quoted)
{
	pid_t		pid;

	signal_catching_mode(PARENT_PROCESS);
	pid = fork();
	if (pid < 0)
		error_display("fork", strerror(errno), 0);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		heredoc_job(sh, hdoc_path, delim, quoted);
	}
	wait_heredoc(sh);
	signal_catching_mode(INTERACTIVE);
}
