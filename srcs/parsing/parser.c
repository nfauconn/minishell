/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:49 by user42            #+#    #+#             */
/*   Updated: 2022/08/18 15:38:40 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	parse(t_sh *sh, t_input *input)
{
	if (!*(input->line_read))
		return (1);
	if (tokenize(input))
		return (1);
	if (!input->token_list)
		return (1);
	print_token_list(input);//DEBUG
	if (lexer(input->token_list))
		return (1);
	if (build_cmd_lst(sh, input->token_list))
		return (1);
//	print_cmd_list(sh);//DEBUG
	return (0);
}
