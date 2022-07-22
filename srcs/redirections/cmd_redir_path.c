/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:28:23 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/23 01:02:02 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static void	set_redir_out(t_list **token, t_cmd *cmd)
{
	if (cmd->outfile_name)
		ft_strdel(&cmd->outfile_name);
	cmd->redir_out_type = (*token)->type;
	cmd->outfile_name = ft_strdup((char *)(*token)->content);
	while ((*token)->next && is_outfilename((*token)->next->type))
	{
		(*token) = (*token)->next;
		ft_strfjoin(&cmd->outfile_name, (char *)(*token)->content);
	}
}

static void	set_redir_in(t_list **token, t_cmd *cmd)
{
	if (cmd->infile_name)
		ft_strdel(&cmd->infile_name);
	cmd->infile_name = ft_strdup((char *)(*token)->content);
	while ((*token)->next && (*token)->next->type == INFILE_NAME)
	{
		(*token) = (*token)->next;
		ft_strfjoin(&cmd->infile_name, (char *)(*token)->content);
	}
}

static void	set_redir(t_sh *sh, t_list **token, t_cmd *cmd)
{
	if ((*token)->type == INFILE_NAME)
	{
		cmd->heredoc_infile = 0;
		set_redir_in(token, cmd);
		if (check_access(cmd->infile_name, R_OK, &cmd->access_error) < 0)
			return ;
	}
	else if ((*token)->type == HEREDOC_DELIM
		|| (*token)->type == QUOTED_HEREDOC_DELIM)
	{
		cmd->heredoc_infile = 1;
		heredoc_set(sh, token, cmd);
	}
	else if (is_outfilename((*token)->type))
	{
		set_redir_out(&(*token), cmd);
		if (access(cmd->outfile_name, F_OK) == SUCCESS && \
			(check_access(cmd->outfile_name, W_OK, &cmd->access_error) < 0))
			return ;
	}
}

void	fill_cmd_redir(t_sh *sh, t_list *token, t_cmd *cmd)
{
	errno = 0;
	while (token && !is_sep(token->type) && !errno)
	{
		set_redir(sh, &token, cmd);
		if (token)
			token = token->next;
	}
}
