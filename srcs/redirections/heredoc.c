/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:34 by user42            #+#    #+#             */
/*   Updated: 2022/07/19 18:26:58 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redir.h"

static void	read_heredoc_nbline(int *nb)
{
	int	fd;

	*nb = 1;
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

static void	heredoc_job(t_sh *sh, char *heredoc_path, char *delim)
{
	int		fd;
	int		nbltotal;
	int		nbl;
	char	*line;
	t_bool	quoted;

	nbl = 0;
	read_heredoc_nbline(&nbltotal);
	fd = open(heredoc_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		exit(errno);
	quoted = (delim[0] == QUOTE || delim[0] == DB_QUOTE);
	delim = ft_substr(delim + quoted, 0, ft_strlen(delim) - 2 * quoted);
	line = readline("> ");
	while (++nbl && line && (line[0] == '\n' || ft_strcmp(line, delim)))
	{
		if (!quoted)
			ft_replace_free_old((void **)&line, expand_string(line, sh));
		ft_putendl_fd(line, fd);
		ft_replace_free_old((void **)&line, readline("> "));
	}
	if (!line)
		ft_printerror("minish: warning: here-document"\
		" at line %d delimited by end-of-file (wanted `%s')\n", nbltotal, delim);
	write_heredoc_nbline(nbltotal += nbl);
	free(line);
	free(delim);
	close(fd);
	exit(0);
}

void	run_heredoc(t_sh *sh, char *heredoc_path, char *delim)
{
	pid_t		pid;
	int			wstatus;

	signal_catching_mode(PARENT_PROCESS);
	pid = fork();
	if (pid < 0)
		error_display("fork", strerror(errno), 0);
	if (pid == 0)
	{
		signal_catching_mode(CHILD_PROCESS);
		heredoc_job(sh, heredoc_path, delim);
	}
	wait(&wstatus);
	signal_catching_mode(INTERACTIVE);
	if (wstatus != 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
}
