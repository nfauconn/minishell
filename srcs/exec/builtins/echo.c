/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:48:38 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/13 13:22:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

int	mini_echo(t_sh *sh, t_cmd *cmd)
{
	int		nl_flag;
	size_t	j;

	(void)sh;
	char **args = cmd->args;
	args++;
	j = 0;
	nl_flag = echo_handle_nlflag(args, &j);
	if (cmd->redir_error)
		return (WRONG_REDIR);
	if (cmd->redir_out == NO_REDIR)
		cmd->redir_out = STDOUT_FILENO;
	while (args[j])
	{
		ft_putstr_fd(args[j], cmd->redir_out);
		if (args[j + 1])
			ft_putstr_fd(" ", cmd->redir_out);
		++j;
	}
	if (nl_flag)
		ft_putstr_fd("\n", cmd->redir_out);
	return (0);
}
