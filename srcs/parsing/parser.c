/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:49 by user42            #+#    #+#             */
/*   Updated: 2022/07/08 14:46:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing(t_sh *sh, t_input *input)
{
	if (tokenizer(input, input->line_read))
		return (FAILURE);
	set_types_for_lex(input->token_list);
	if (lexer(input->token_list))
		return (FAILURE);
	complete_types(input->token_list);
	token_expand(input->token_list, sh);
	token_to_cmd_lst(sh, input->token_list);
	#ifdef DEBUG
	t_cmd	*tmp = sh->cmd_list;
	while(tmp)
	{
//		ft_str_array_display(tmp->args);
		printf("cmd n.%zu = %s -- red_i = %d | red_o = %d\n", tmp->index, tmp->name, tmp->redir_in, tmp->redir_out);
		tmp = tmp->next;
	}
	#endif
	return (SUCCESS);
}

/*
	#ifdef DEBUG
	display_token_list(input->token_list);
	#endif

*/