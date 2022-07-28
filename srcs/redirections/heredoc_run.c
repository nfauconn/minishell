/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/07/28 20:17:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static void end_heredoc(char **line, int fd)
{
	ft_strdel(line);
	close(fd);
	exit(0);
}

static void	cancel_heredoc(size_t line_nb, char *delim)
{
	ft_printerror("minish: warning: here-document"\
	" at line %d delimited by end-of-file (wanted `%s')\n", line_nb, delim);
}

static void	putstr_heredoc(t_sh *sh, char **line, int fd, t_bool quoted)
{
	char	*new_line;

	if (!quoted)
		ft_replace_free_old((void **)line, expand_string(*line, sh));
	ft_putendl_fd(*line, fd);
	sh->line_nb++;
	new_line = readline("> ");
	ft_replace_free_old((void **)line, new_line);
}

static void	heredoc_job(t_sh *sh, char *hdoc_path, char *delim, t_bool quoted)
{
	int		fd;
	char	*line;

	fd = open(hdoc_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		exit(1);
	line = readline("> ");
	sh->line_nb++;
	while (line && (line[0] == '\n' || ft_strcmp(line, delim)) != SUCCESS)
		putstr_heredoc(sh, &line, fd, quoted);
	if (!line)
		cancel_heredoc(sh->line_nb, delim);
	end_heredoc(&line, fd);
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
		signal_catching_mode(HEREDOC);
		heredoc_job(sh, hdoc_path, delim, quoted);
	}
	wait_heredoc();
	signal_catching_mode(INTERACTIVE);
}
