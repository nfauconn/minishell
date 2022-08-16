/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/08/16 17:23:14 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static void	exit_clear_heredoc(t_sh *sh, char **line, int fd)
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
		ft_replacefree((void **)line, expand_str(*line, ft_strlen(*line), sh));
	ft_putendl_fd(*line, fd);
	sh->line_nb++;
	new_line = readline("> ");
	ft_replacefree((void **)line, new_line);
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
	while (line && (line[0] == '\n' || ft_strcmp(line, delim)) != OK)
		putstr_heredoc(sh, &line, fd, quoted);
	if (!line)
		display_warning(sh, delim);
	exit_clear_heredoc(sh, &line, fd);
}

t_bool	run_heredoc(t_sh *sh, char *hdoc_path, char *delim, t_bool quoted)
{
	pid_t		pid;
	t_bool		ret;

	ret = 0;
	signal_catching_mode(PARENT_PROCESS);
	pid = fork();
	if (pid < 0)
		error_display("fork", strerror(errno), 0);
	if (pid == 0)
	{
		signal_catching_mode(HEREDOC);
		heredoc_job(sh, hdoc_path, delim, quoted);
	}
	if (wait_heredoc())
		ret = 1;
	signal_catching_mode(INTERACTIVE);
	return (ret);
}
