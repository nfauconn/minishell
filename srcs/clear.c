/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:14:36 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/30 19:33:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"

static void	clear_cmd_params(t_cmd *cmd)
{
	if (cmd->args)
		ft_strarray_clear(cmd->args);
	if (cmd->possible_paths)
		ft_strarray_clear(cmd->possible_paths);
	if (cmd->path)
		ft_strdel(&cmd->path);
	if (cmd->infile_name)
		ft_strdel(&cmd->infile_name);
	if (cmd->outfile_name)
		ft_strdel(&cmd->outfile_name);
}

void	clear_cmd_list(t_cmd *cmd)
{
	t_cmd	*to_del;

	while (cmd)
	{
		close_cmd_redirs(cmd);
		clear_cmd_params(cmd);
		to_del = cmd;
		cmd = cmd->next;
		free(to_del);
		to_del = NULL;
	}
	cmd = NULL;
}

void	clear_input(t_input *input)
{
	if (input)
	{
		if (input->line_read)
			ft_strdel(&input->line_read);
		if (input->token_list)
			ft_lstclear(&input->token_list, free);
		input = NULL;
	}
}

void	clear_sh(t_sh *sh)
{
	sh->level = 0;
	sh->line_nb = 0;
	sh->cmd_nb = 0;
	if (sh->cmd_list)
		clear_cmd_list(sh->cmd_list);
	sh->heredoc_nb = 0;
	if (sh->env)
		ft_lstclear(&sh->env, free);
}
