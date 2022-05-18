/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:52 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/18 17:52:55 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd(char **args)
{
	DIR*	dir;

	if (!args[0])
		errno = EINVAL;
	else if (args[1])
		errno = E2BIG;
	else
	{
		dir = opendir(args[0]);
		if (!dir)
			perror("pwd");
		else
			chdir(args[0]);
	}
	return (errno);
}
