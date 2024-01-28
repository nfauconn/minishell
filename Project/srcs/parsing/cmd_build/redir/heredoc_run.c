/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/09/14 22:45:08 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

extern uint8_t	g_last_status;

static void	clear_heredoc(char **line, int fd)
{
	ft_strdel(line);
	close(fd);
}

static void	putstr_heredoc(t_sh *sh, char **line, int fd, t_bool quoted)
{
	char	*new_line;

	if (ft_strcmp(*line, "\0") && !quoted)
		ft_replacefree((void **)line, expand_str(*line, ft_strlen(*line), sh));
	ft_putendl_fd(*line, fd);
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
	while (line && ft_strcmp(line, delim) != OK)
		putstr_heredoc(sh, &line, fd, cmd->redir_in.quoted_delim);
	if (access("/dev/stdin", R_OK))
	{
		cmd->redir_in.heredoc_ctrlc = 1;
		dup2(stdin, STDIN_FILENO);
	}
	else if (!line)
		ft_printerror("\n");
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
