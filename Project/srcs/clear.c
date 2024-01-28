/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:14:36 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/14 16:07:10 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"

void	clear_cmd(t_cmd *cmd)
{
	if (cmd->args)
		ft_strarrayclear(&cmd->args);
	if (cmd->redir_in.filename)
	{
		if (cmd->redir_in.fd > STDERR_FILENO)
			close(cmd->redir_in.fd);
		if (cmd->redir_in.is_heredoc)
		{
			ft_strdel(&cmd->redir_in.delim);
			unlink(cmd->redir_in.filename);
		}
		ft_strdel(&cmd->redir_in.filename);
	}
	if (cmd->redir_out.filename)
	{
		if (cmd->redir_out.fd > STDERR_FILENO)
			close(cmd->redir_out.fd);
		ft_strdel(&cmd->redir_out.filename);
	}
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
	sh->cmd_nb = 0;
	ft_strdel(&sh->cwd);
	if (sh->cmd_list)
		clear_cmd_list(&sh->cmd_list);
	sh->heredoc_nb = 0;
	if (sh->env)
		ft_lstclear(&sh->env, free);
	rl_clear_history();
}
