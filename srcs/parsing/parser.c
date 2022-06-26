/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:49 by user42            #+#    #+#             */
/*   Updated: 2022/06/26 22:30:04 by user42           ###   ########.fr       */
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

	#ifdef DEBUG
	display_token_list(input->token_list);
	#endif
	
	complete_types(input->token_list);

	token_expand(input->token_list, sh);
	token_to_cmd_lst(sh, input->token_list);

	#ifdef DEBUG
	t_cmd	*tmp = sh->cmd_list;
	while(tmp)
	{
		ft_str_array_display(tmp->args);
		tmp = tmp->next;
	}
	#endif

	return (SUCCESS);
}
