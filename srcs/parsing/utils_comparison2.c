/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_comparison2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:56:44 by user42            #+#    #+#             */
/*   Updated: 2022/06/29 20:38:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(int c)
{
	return (!is_quote(c) && !is_redir(c) && !is_blank(c) && !is_sep(c));
}

int	is_builtin(char *cmd_name)
{
	int			i;
	static char	*builtins[7] = {"cd", "echo", "env", "export", "pwd", "unset", 0};

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
