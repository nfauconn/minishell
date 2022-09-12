/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:48:38 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 19:14:48 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_redir_out(t_cmd *cmd)
{
	while (cmd->redir_out && cmd->redir_out->next)
		cmd->redir_out = cmd->redir_out->next;
	return (cmd->redir_out->fd);
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
			if (i == 1 || args[*j][i] != '\0')
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
	int		fd_out;

	args = cmd->args;
	args++;
	j = 0;
	nl_flag = echo_handle_nlflag(args, &j);
	if (sh->cmd_nb == 1 && cmd->redir_out)
		fd_out = handle_redir_out(cmd);
	else
		fd_out = STDOUT_FILENO;
	while (args[j])
	{
		ft_putstr_fd(args[j], fd_out);
		if (args[j + 1])
			ft_putstr_fd(" ", fd_out);
		++j;
	}
	if (nl_flag)
		ft_putstr_fd("\n", fd_out);
	return (0);
}
