/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:02:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/18 16:56:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_close_old(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	if (old_fd != new_fd)
		close(old_fd);
}

void	close_if_exists(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
}

int	open_w_err_check(int fd, char *file_path, int flag)
{
	if (flag == O_RDONLY)
		fd = open(file_path, O_RDWR);
	else if ((int)flag == (int)O_WRONLY)
		fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		error_display(file_path, strerror(errno));
		fd = -2;
	}
	return (fd);
}

void	pipe_w_err_check(int *redir)
{
	if (pipe(redir) == -1)
		error_display("pipe: ", strerror(errno));
}
