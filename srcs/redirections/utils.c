/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:02:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/11 22:11:31 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

void	dup2_close_old(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	if (old_fd != new_fd && old_fd > STDERR_FILENO)
		close(old_fd);
}

int	open_w_err_check(int fd, char *file_path, int flag)
{
	if (flag == O_RDONLY)
		fd = open(file_path, O_RDWR);
	else if ((int)flag == (int)O_WRONLY)
		fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		error_display(file_path, strerror(errno), 0);
		fd = -2;
	}
	return (fd);
}
