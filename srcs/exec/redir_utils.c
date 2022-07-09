/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:02:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/08 14:50:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	dup2_close_old(int old_fd, int new_fd)
{
	#ifdef DEBUG
	ft_printerror ("dup2_close_old : %d becomes %d (close %d)\n", old_fd, new_fd, old_fd);
	#endif
	dup2(old_fd, new_fd);
	if (old_fd != new_fd)
		close(old_fd);
}

void	close_if_no_std(int fd)
{
	if (fd > STDERR_FILENO)
	{
		#ifdef DEBUG
		ft_printerror ("close_if_no_std : closing fd n.%d\n", fd);
		#endif
		close(fd);
	}
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
