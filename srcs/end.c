/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:09:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/20 18:23:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_sh(t_sh *sh)
{
	t_cmd	*to_del;

	(void)sh;
	while (sh->cmd_list)
	{
		if (sh->cmd_list->args)
			ft_str_array_free(sh->cmd_list->args);
		if (sh->cmd_list->env)
			ft_str_array_free(sh->cmd_list->env);
		if (sh->cmd_list->possible_paths)
			ft_str_array_free(sh->cmd_list->possible_paths);
		if (sh->cmd_list->path)
			free(sh->cmd_list->path);
		to_del = sh->cmd_list;
		sh->cmd_list = sh->cmd_list->next;
		free(to_del);
	}
}

void	end_input(t_input *input)
{
	if (input->line_read)
		ft_strdel(&input->line_read);
	if (input->token_list)
		ft_lstclear(&input->token_list, free);
	input = NULL;
}

void	end(t_input *input, t_sh *sh)
{
	if (input)
		end_input(input);
	if (sh)
		end_sh(sh);
}