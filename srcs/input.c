/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:10:00 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/15 22:19:14 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_sh *sh)
{
	char	*prompt;
	char	*line_read;

	prompt = build_prompt();
	line_read = readline(prompt);
	if (!line_read)
	{
		ft_strdel(&prompt);
		exit_clear_minish(sh, 0);
	}
	if (line_read && *line_read == '\0')
		redisplay_prompt();
	if (line_read && *line_read)
		add_history(line_read);
	sh->line_nb++;
	free(prompt);
	return (line_read);
}

int	init_input(t_sh *sh, t_input *input)
{
	input->line_read = get_input(sh);
	input->token_list = NULL;
	return (0);
}
