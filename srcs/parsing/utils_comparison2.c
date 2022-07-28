/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_comparison2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:56:44 by user42            #+#    #+#             */
/*   Updated: 2022/07/27 21:46:11 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_metacharacter(int c)
{
	return (is_blank(c) || is_rediroperator(c) || is_sep(c));
}

int	is_infilename(int c)
{
	return (c == INFILE_NAME);
}

int	is_heredoc_delim(int c)
{
	return (c == HEREDOC_DELIM || c == QUOTED_HEREDOC_DELIM);
}

int	is_builtin(char *cmd_name)
{
	int			i;
	static char	*builtins[8] = {"cd", "echo", "env", "exit", "export", \
	"pwd", "unset", 0};

	if (!cmd_name || !*cmd_name)
		return (-1);
	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(cmd_name, builtins[i]))
			return (i);
		i++;
	}
	return (-1);
}
