/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:48:38 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/18 23:42:28 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	handle_redirection(t_sh *sh, t_cmd *cmd)
{
	if (sh->cmd_nb > 1)
	{
		cmd->redir_in.fd = STDIN_FILENO;
		cmd->redir_out.fd = STDOUT_FILENO;
	}
}

static int	echo_handle_nlflag(char **args, size_t *j)
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
	char	**args;
	int		nl_flag;
	size_t	j;

	args = cmd->args;
	args++;
	j = 0;
	nl_flag = echo_handle_nlflag(args, &j);
	handle_redirection(sh, cmd);
	while (args[j])
	{
		ft_putstr_fd(args[j], cmd->redir_out.fd);
		if (args[j + 1])
			ft_putstr_fd(" ", cmd->redir_out.fd);
		++j;
	}
	if (nl_flag)
		ft_putstr_fd("\n", cmd->redir_out.fd);
	return (0);
}
