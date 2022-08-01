/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:49 by user42            #+#    #+#             */
/*   Updated: 2022/08/01 18:22:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing(t_sh *sh, t_input *input)
{
	if (!*(input->line_read))
		return (1);
	if (tokenizer(input, input->line_read))
		return (1);
	if (!input->token_list || lexer(input->token_list))
		return (1);
	token_expand(input->token_list, sh);
	set_token_types(input->token_list);
	token_to_cmd_lst(sh, input->token_list);
	return (SUCCESS);
}

/*
ft_printerror("TOKEN_LIST :\n");
display_token_list(input->token_list);
ft_printerror("___________\n\n");

ft_printf("\n");
t_cmd	*tmp = sh->cmd_list;
while(tmp)
{
ft_str_array_display(tmp->args);
ft_printf("\n", 1);
tmp = tmp->next;
}
*/