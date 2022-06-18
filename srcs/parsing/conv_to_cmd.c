/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:36:26 by user42            #+#    #+#             */
/*   Updated: 2022/06/18 19:20:08 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_to_cmd_lst(t_sh *sh, t_list *token)
{
	size_t	i;
	t_cmd	*new_cmd;
	t_cmd 	**head;

	sh->cmd_nb = get_cmd_nb(token);
//	printf("cmd_nb = %zu\n", sh->cmd_nb);
	head = &sh->cmd_list;
	i = 0;
	while (token)
	{
		new_cmd = create_new_cmd(token);
		new_cmd->index = i;
		add_cmd_to_list(head, new_cmd);
		while (token && !is_separator(token->type))
			token = token->next;
		if (token && is_separator(token->type))
			token = token->next;
		i++;
	}

//just to display
/* 	t_cmd	*cmd;
	cmd = *head;
	while (cmd)
	{
		ft_tab_display(cmd->cmd_tab);
		cmd = cmd->next;
	} */
}
