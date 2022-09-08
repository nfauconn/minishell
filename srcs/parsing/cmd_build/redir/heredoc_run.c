/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/09/08 18:18:21 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

extern uint8_t	g_last_status;

static void	clear_heredoc(char **line, int fd)
{
	ft_strdel(line);
	close(fd);
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

static t_bool	heredoc_job(t_sh *sh, char *hdoc_path, char *delim, t_cmd *cmd)
{
	int		fd;
	int		stdin;
	char	*line;

	fd = open(hdoc_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (2);
	stdin = dup(STDIN_FILENO);
	line = readline("> ");
	if (sh->heredoc_nb > 1)
		sh->line_nb++;
	while (line && ft_strcmp(line, delim) != OK)
		putstr_heredoc(sh, &line, fd, cmd->redir_in.quoted_delim);
	if (access("/dev/stdin", R_OK))
	{
		cmd->redir_in.heredoc_ctrlc = 1;
		dup2(stdin, STDIN_FILENO);
	}
	else if (!line)
		display_warning(sh, delim);
	close(stdin);
	clear_heredoc(&line, fd);
	return (0);
}

t_bool	run_heredoc(t_sh *sh, char *hdoc_path, char *delim, t_cmd *cmd)
{
	signal_catching_mode(HEREDOC);
	heredoc_job(sh, hdoc_path, delim, cmd);
	signal_catching_mode(INTERACTIVE);
	if (cmd->redir_error || cmd->redir_in.heredoc_ctrlc != 0)
		return (1);
	return (0);
}
