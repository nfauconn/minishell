/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/07/12 22:52:59 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

static void	heredoc_job(t_sh *sh, char *delim, int p[2])
{
	int		fd;
	int		nbltotal;
	int		nbl;
	char	*line;
	char	*heredoc_path;
	char	*heredoc_no;

	nbl = 0;
	nbltotal = 1;
	read_heredoc_nbline(&nbltotal);
	heredoc_no = ft_itoa(sh->heredoc_nb);
	heredoc_path = ft_strjoin("/tmp/.here_doc", heredoc_no);
	close(p[0]);
	ft_putstr_fd(heredoc_path, p[1]);
	close(p[1]);
	ft_strdel(&heredoc_no);
	fd = open("/tmp/.here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		exit(-1);
	line = readline("> ");
	while (++nbl && line && (line[0] == '\n' || ft_strcmp(line, delim)))
	{
		ft_replace_free_old((void **)&line, expand_string(line, sh));
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	if (!line)
		ft_printerror("bash: warning: here-document"\
		" at line %d delimited by end-of-file (wanted `%s')\n", nbltotal, delim);
	write_heredoc_nbline(nbltotal += nbl);
	free(line);
	close(fd);
	exit(0);
}

char	*run_heredoc(t_sh *sh, char *delim)
{
	char		*path;
	pid_t		pid;
	int			p[2];
	int			wstatus;

	signal_catching_mode(PARENT_PROCESS);
	if (pipe(p) < 0)
		error_display("pipe", strerror(errno), 0);
	pid = fork();
	if (pid < 0)
		error_display("fork", strerror(errno), 0);
	if (pid == 0)
	{
		signal_catching_mode(CHILD_PROCESS);
		heredoc_job(sh, delim, p);
	}
	close(p[1]);
	path = (char *)malloc(sizeof(char) * 20);
	ft_bzero(path, 20);
	read(p[0], &path, 20);
	close(p[0]);
	wait(&wstatus);
	signal_catching_mode(INTERACTIVE);
	if (wstatus != 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	return (path);
/* 	*fd = open("/tmp/.here_doc", O_RDONLY);
	if (*fd < 0)
		error_display("here_doc", strerror(errno), 0); */
}
