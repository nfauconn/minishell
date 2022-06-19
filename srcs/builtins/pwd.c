/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:51:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/19 12:34:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	pwd with no options (and no arguments)
*	@return 0 Successful completion. >0 An error occurred.
*/
int	builtin_pwd(char **args)
{
	char	*name;

	(void)args;
	name = getcwd(NULL, 0);
	if (!name)
	{
		perror("pwd");
		return (errno);
	}
	printf("%s\n", name);
	return (0);
}
