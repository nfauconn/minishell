/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 11:46:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static void exit_clear_heredoc(t_sh *sh, char **line, int fd)
{
	ft_strdel(line);
	close(fd);
	exit_clear_child(sh, 0);
}

static void	display_warning(t_sh *sh, char *delim)
{
	ft_printerror("minish: warning: here-document"\
	" at line %d delimited by end-of-file (wanted `%s')\n", sh->line_nb, delim);
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
		exit_clear_child(sh, 1);
	line = readline("> ");
	if (sh->heredoc_nb > 1)
		sh->line_nb++;
	while (line && (line[0] == '\n' || ft_strcmp(line, delim)) != SUCCESS)
		putstr_heredoc(sh, &line, fd, quoted);
	if (!line)
		display_warning(sh, delim);
	exit_clear_heredoc(sh, &line, fd);
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
