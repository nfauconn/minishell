/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:51:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/18 17:51:36 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int pwd(char **args)
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
