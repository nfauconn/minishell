/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:48:38 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/18 17:48:52 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int echo(char **args)
{
	int		nl_flag;
	size_t	j;
	size_t	i;

	j = 0;
	nl_flag = 0;
	while (args[j])
	{
		if (args[j][0] == '-')
		{
			i = 1;
			while (args[j][i] == 'n')
				++i;
			if (args[j][i] != '\0')
				break;
			nl_flag = 1;
		}
		else
			break;
		++j;
	}
	while (args[j])
	{
		printf("%s", args[j]);
			if (args[j + 1])
				printf(" ");
		++j;
	}
	if (!nl_flag)
		printf("\n");
	return (0);
}