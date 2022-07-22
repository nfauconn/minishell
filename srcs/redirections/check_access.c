/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:57:11 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/23 00:58:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static void	fill_access_error(char **to_fill, char *path, int access_errno)
{
	char	*tmp;

	*to_fill = ft_strjoin(path, ": ");
	tmp = *to_fill;
	*to_fill = ft_strjoin(tmp, strerror(access_errno));
	free(tmp);
}

int	check_access(char *filename, int flag, char **access_error)
{
	if (access(filename, flag) < 0)
	{
		fill_access_error(access_error, filename, errno);
		return (-1);
	}
	return (0);
}
