/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:48:38 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/19 12:46:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_handle_nlflag(char **args, size_t *j)
{
	int		nl_flag;
	size_t	i;

	nl_flag = 1;
	while (args[*j])
	{
		if (args[*j][0] == '-')
		{
			i = 1;
			while (args[*j][i] == 'n')
				++i;
			if (args[*j][i] != '\0')
				break ;
			nl_flag = 0;
		}
		else
			break ;
		++*j;
	}
	return (nl_flag);
}

int	builtin_echo(char **args)
{
	int		nl_flag;
	size_t	j;

	j = 0;
	nl_flag = echo_handle_nlflag(args, &j);
	while (args[j])
	{
		printf("%s", args[j]);
		if (args[j + 1])
			printf(" ");
		++j;
	}
	if (nl_flag)
		printf("\n");
	return (0);
}
