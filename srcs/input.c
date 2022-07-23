/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:10:00 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/23 17:18:09 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_sh *sh)
{
	char	*line_read;

	line_read = readline("minish> ");
	if (line_read && *line_read)
		add_history(line_read);
	else if (line_read && *line_read == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (!line_read)
	{
		ft_putstr_fd("exit\n", 1);
		free(line_read);
		ft_lstclear(&sh->env, free);
		ft_strdel(&sh->last_status_str);
		exit(1);
	}
	return (line_read);
}
