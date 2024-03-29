/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:28:23 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/14 22:31:16 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static t_bool	open_redir_out(t_cmd *cmd)
{
	if (cmd->redir_out.is_append)
		cmd->redir_out.fd = open(cmd->redir_out.filename, \
			O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		cmd->redir_out.fd = open(cmd->redir_out.filename, \
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (cmd->redir_out.fd < 0)
	{
		error_display(cmd->redir_out.filename, strerror(errno), 0);
		return (1);
	}
	return (0);
}

static t_bool	set_redir_outfile(t_sh *sh, t_cmd *cmd, char *token)
{
	if (cmd->redir_out.filename)
		ft_strdel(&cmd->redir_out.filename);
	if (cmd->redir_out.fd > 2)
		close(cmd->redir_out.fd);
	cmd->redir_out.is_append = !ft_strncmp(token, ">>", 2);
	while (is_redir(*token))
		token++;
	while (is_blank(*token))
		token++;
	if (*token == '$' && check_ambig(sh, token))
	{
		error_display(token, "ambiguous redirect", 0);
		return (1);
	}
	cmd->redir_out.filename = expand(token, sh);
	ft_replacefree((void **)&cmd->redir_out.filename, \
		remove_quote(cmd->redir_out.filename));
	open_redir_out(cmd);
	close(cmd->redir_out.fd);
	return (0);
}

static t_bool	set_redir_heredoc(t_sh *sh, t_cmd *cmd, char *token)
{
	if (cmd->redir_in.filename)
	{
		if (cmd->redir_in.is_heredoc)
			unlink(cmd->redir_in.filename);
		ft_strdel(&cmd->redir_in.filename);
	}
	while (is_redir(*token))
		token++;
	while (is_blank(*token))
		token++;
	cmd->redir_in.is_heredoc = 1;
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		cmd->redir_in.quoted_delim = 1;
	else
		cmd->redir_in.quoted_delim = 0;
	return (heredoc_set(sh, cmd, token));
}

static t_bool	set_redir_infile(t_sh *sh, t_cmd *cmd, char *token)
{
	if (cmd->redir_in.filename)
	{
		if (cmd->redir_in.is_heredoc)
			unlink(cmd->redir_in.filename);
		ft_strdel(&cmd->redir_in.filename);
	}
	while (is_redir(*token))
		token++;
	while (is_blank(*token))
		token++;
	cmd->redir_in.is_heredoc = 0;
	if (*token == '$' && check_ambig(sh, token))
	{
		error_display(token, "ambiguous redirect", 0);
		return (1);
	}
	cmd->redir_in.filename = expand(token, sh);
	ft_replacefree((void **)&cmd->redir_in.filename, \
		remove_quote(cmd->redir_in.filename));
	return (check_access(cmd->redir_in.filename, F_OK | R_OK));
}

t_bool	set_redir(t_sh *sh, t_cmd *cmd, char *token)
{
	t_bool	ret;

	ret = 0;
	if (!ft_strncmp(token, "<<", 2))
		ret = set_redir_heredoc(sh, cmd, token);
	else if (!ft_strncmp(token, "<", 1))
		ret = set_redir_infile(sh, cmd, token);
	else if (!ft_strncmp(token, ">>", 2))
		ret = set_redir_outfile(sh, cmd, token);
	else if (!ft_strncmp(token, ">", 1))
		ret = set_redir_outfile(sh, cmd, token);
	cmd->redir_error = ret;
	return (ret);
}
