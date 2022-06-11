/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_conv_to_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:36:26 by user42            #+#    #+#             */
/*   Updated: 2022/06/11 11:48:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_to_cmd_lst(t_sh *sh, t_list *token)
{
	t_cmd	*new_cmd;
	t_cmd 	*head;

	head = sh->cmd_list;
	while (token)
	{
		new_cmd = NULL;
		new_cmd = create_new_cmd(token);
		add_cmd_to_list(&head, new_cmd);
		while (token && !is_separator(token->type))
			token = token->next;
		if (token && is_separator(token->type))
			token = token->next;
	}

//just to display
	t_cmd	*cmd;
	cmd = head;
	while (cmd)
	{
		ft_tab_display(cmd->cmd_tab);
		cmd = cmd->next;
	}
}
