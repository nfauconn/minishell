/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:09:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/05 16:19:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_sh(t_sh *sh)
{
	t_cmd	*to_del;

	while (sh->cmd_list)
	{
		close_if_no_std(sh->cmd_list->redir_in);
		close_if_no_std(sh->cmd_list->redir_out);
		if (sh->cmd_list->args)
			ft_str_array_free(sh->cmd_list->args);
		if (sh->cmd_list->env)
			ft_str_array_free(sh->cmd_list->env);
		if (sh->cmd_list->env_paths)
			ft_str_array_free(sh->cmd_list->env_paths);
		if (sh->cmd_list->path)
			free(sh->cmd_list->path);
		to_del = sh->cmd_list;
		sh->cmd_list = sh->cmd_list->next;
		free(to_del);
	}
}

void	clear_input(t_input *input)
{
	if (input->line_read)
		ft_strdel(&input->line_read);
	if (input->token_list)
		ft_lstclear(&input->token_list, free);
	input = NULL;
}

void	clear(t_input *input, t_sh *sh)
{
	if (input)
		clear_input(input);
	if (sh)
		clear_sh(sh);
}

void	exit_clear(t_sh *sh, unsigned int exit_code)
{
	ft_lstclear(&sh->env, free);
	clear_sh(sh);
	exit(exit_code);
}
