/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:12:39 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/22 22:33:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_cmd_settings(t_cmd *cmd)
{
	if (cmd->args)
		ft_str_array_free(cmd->args);
	if (cmd->env)
		ft_str_array_free(cmd->env);
	if (cmd->env_paths)
		ft_str_array_free(cmd->env_paths);
	if (cmd->path)
		ft_strdel(&cmd->path);
	if (cmd->infile_name)
		ft_strdel(&cmd->infile_name);
	if (cmd->outfile_name)
		ft_strdel(&cmd->outfile_name);
	if (cmd->access_error)
		ft_strdel(&cmd->access_error);
}

void	clear_sh(t_sh *sh)
{
	t_cmd	*to_del;

	while (sh->cmd_list)
	{
		close_if_no_std(sh->cmd_list->redir_in);
		if (sh->cmd_list->heredoc_infile)
			unlink(sh->cmd_list->infile_name);
		close_if_no_std(sh->cmd_list->redir_out);
		clear_cmd_settings(sh->cmd_list);
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
