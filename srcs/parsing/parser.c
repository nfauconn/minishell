/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:49 by user42            #+#    #+#             */
/*   Updated: 2022/06/21 12:50:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_input *input, t_sh *sh)
{
	if (tokenizer(input, input->line_read) == FAILURE)
		return (FAILURE);
	set_types_for_lex(input->token_list);
	if (lexer(input->token_list) == FAILURE)
		return (FAILURE);
	token_expand(input->token_list, sh->env);
	set_types_complete(input->token_list);
	token_to_cmd_lst(sh, input->token_list);
	return (SUCCESS);
}
