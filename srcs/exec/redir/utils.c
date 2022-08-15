/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:02:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 19:54:55 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

void	dup2_close_old(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	if (old_fd != new_fd)
		close(old_fd);
}
