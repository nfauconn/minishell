/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:36:26 by user42            #+#    #+#             */
/*   Updated: 2022/07/08 13:20:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	token_to_cmd_lst(t_sh *sh, t_list *token)
{
	size_t	i;
	t_cmd	*new_cmd;
	t_cmd	**head;

	sh->cmd_nb = get_cmd_nb(token);
	head = &sh->cmd_list;
	i = 0;
	while (token)
	{
		new_cmd = create_new_cmd(sh, token);
		new_cmd->index = i;
		add_cmd_to_list(head, new_cmd);
		while (token && !is_sep(token->type))
			token = token->next;
		if (token && is_sep(token->type))
			token = token->next;
		i++;
	}
}
