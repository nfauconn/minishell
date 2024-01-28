/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:49 by user42            #+#    #+#             */
/*   Updated: 2022/09/14 21:21:39 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern uint8_t	g_last_status;

t_bool	parse(t_sh *sh, t_input *input)
{
	if (!*(input->line_read))
		return (1);
	if (tokenize(input))
	{
		clear_input(input);
		g_last_status = 2;
		return (1);
	}
	if (!input->token_list)
		return (1);
	if (lexer(input->token_list))
	{
		clear_input(input);
		g_last_status = 2;
		return (1);
	}
	if (build_cmd_lst(sh, input->token_list))
	{
		clear_input(input);
		return (1);
	}
	return (0);
}

/*
** print_token_list(input);
** print_commands(sh);
*/