/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:14:36 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/28 21:14:38 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd_params(t_cmd *cmd)
{
	if (cmd->args)
		ft_strarray_clear(cmd->args);
	if (cmd->env)
		ft_strarray_clear(cmd->env);
	if (cmd->env_paths)
		ft_strarray_clear(cmd->env_paths);
	if (cmd->path)
		ft_strdel(&cmd->path);
	if (cmd->infile_name)
		ft_strdel(&cmd->infile_name);
	if (cmd->outfile_name)
		ft_strdel(&cmd->outfile_name);
}

static void	close_cmd_redirs(t_cmd *cmd)
{
	close_if_no_std(cmd->redir_in);
	if (cmd->heredoc_infile)
		unlink(cmd->infile_name);
	close_if_no_std(cmd->redir_out);	
}

void	clear_cmd_list(t_cmd *cmd)
{
	t_cmd	*to_del;

	while (cmd)
	{
		close_cmd_redirs(cmd);
		free_cmd_params(cmd);
		to_del = cmd;
		cmd = cmd->next;
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

void	reset_sh(t_sh *sh)
{
	if (sh->env)
		ft_lstclear(&sh->env, free);
	reset_for_new_input(sh, NULL);
	ft_bzero(sh, sizeof(sh));
}
