/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:57:11 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 15:20:58 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_bool	check_access(char *filename, int flag)
{
	if (access(filename, flag) < 0)
	{
		error_display(filename, strerror(errno), 0);
		return (1);
	}
	return (0);
}
