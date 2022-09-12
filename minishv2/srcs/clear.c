/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:14:36 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 18:03:58 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"

void	clear_redir_in(t_redir **redir_in)
{
	if ((*redir_in)->fd > STDERR_FILENO)
		close((*redir_in)->fd);
	if ((*redir_in)->is_heredoc)
		unlink((*redir_in)->filename);
	ft_strdel(&(*redir_in)->filename);
	free(*redir_in);
	(*redir_in) = NULL;
}

void	clear_redir_out(t_redir **redir_out)
{
	t_redir	*to_clear;

	while (*redir_out)
	{
		if ((*redir_out)->filename)
		{
			if ((*redir_out)->fd > STDERR_FILENO)
				close((*redir_out)->fd);
			ft_strdel(&(*redir_out)->filename);
		}
		to_clear = *redir_out;
		*redir_out = (*redir_out)->next;
		free(to_clear);
	}
}

void	clear_cmd(t_cmd *cmd)
{
	if (cmd->args)
		ft_strarrayclear(&cmd->args);
	if (cmd->redir_in)
		clear_redir_in(&cmd->redir_in);
	if (cmd->redir_out)
		clear_redir_out(&cmd->redir_out);
}

void	clear_cmd_list(t_cmd **cmd)
{
	t_cmd	*to_del;

	while (*cmd)
	{
		clear_cmd(*cmd);
		to_del = *cmd;
		*cmd = (*cmd)->next;
		free(to_del);
		to_del = NULL;
	}
	*cmd = NULL;
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
		clear_cmd_list(&sh->cmd_list);
	sh->heredoc_nb = 0;
	if (sh->env)
		ft_lstclear(&sh->env, free);
	rl_clear_history();
}
