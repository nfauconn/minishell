/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:52 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/19 12:34:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **args)
{
	DIR	*dir;

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
