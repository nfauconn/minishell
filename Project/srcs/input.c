/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:10:00 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/15 00:08:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern uint8_t	g_last_status;

char	*get_input(t_sh *sh)
{
	char	*prompt;
	char	*line_read;

	prompt = build_prompt(sh->env);
	if (!prompt)
		perror_exit_clear(sh, "get_input", "malloc internal error", 2);
	rl_outstream = stderr;
	line_read = readline(prompt);
	free(prompt);
	if (!line_read)
		exit_clear_minish(sh, g_last_status);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int	init_input(t_sh *sh, t_input *input)
{
	input->line_read = get_input(sh);
	input->token_list = NULL;
	return (0);
}
