/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:41:07 by user42            #+#    #+#             */
/*   Updated: 2022/06/11 11:48:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_input *input, t_sh *sh)
{
	set_types_to_expand(input->token_list);
	token_expand(input->token_list, sh->env);
	complete_types(input->token_list);
	ft_lstiter(input->token_list, display_token_list);

	sh->cmd_nb = get_cmd_nb(input->token_list);
	printf("cmd_nb = %zu\n", sh->cmd_nb);

	token_to_cmd_lst(sh, input->token_list);


//	cmd_redirections(input->token_list);
	return (1);
}