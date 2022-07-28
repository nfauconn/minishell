/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:57:11 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/27 21:52:51 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

int	check_access(char *filename, int flag)
{
	if (access(filename, flag) < 0)
	{
		error_display(filename, strerror(errno), 0);
		return (1);
	}
	return (0);
}
