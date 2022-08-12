/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:28:23 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 00:37:35 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static t_bool	set_redir_append(t_sh *sh, t_cmd *cmd, char *token)
{
	if (cmd->redir_out.filename)
		ft_strdel(&cmd->redir_out.filename);
	while (is_rediroperator(*token))
		token++;
	while (is_blank(*token))
		token++;
	cmd->redir_out.is_append = 1;
	if (*token == '$' && is_ambiguous_redir(sh, token))
	{
		error_display(token, "ambiguous redirect", 0);
		return (1);
	}
	cmd->redir_out.filename = expand(token, sh);
	return (0);
}

static t_bool	set_redir_outfile(t_sh *sh, t_cmd *cmd, char *token)
{
	if (cmd->redir_out.filename)
		ft_strdel(&cmd->redir_out.filename);
	while (is_rediroperator(*token))
		token++;
	while (is_blank(*token))
		token++;
	cmd->redir_out.is_append = 0;
	if (*token == '$' && is_ambiguous_redir(sh, token))
	{
		error_display(token, "ambiguous redirect", 0);
		return (1);
	}
	cmd->redir_out.filename = expand(token, sh);
	return (0);
}

static t_bool	set_redir_heredoc(t_sh *sh, t_cmd *cmd, char *token)
{
	/*
	char	*tmp;
	char	*start;
	char	quote;
	size_t	new_size;
	char	*ret;
	*/
	if (cmd->redir_in.filename)
	{
		if (cmd->redir_in.is_heredoc)
			unlink(cmd->redir_in.filename);
		ft_strdel(&cmd->redir_in.filename);
	}
	while (is_rediroperator(*token))
		token++;
	while (is_blank(*token))
		token++;
	cmd->redir_in.is_heredoc = 1;
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		cmd->redir_in.quoted_delim = 1;
	else
		cmd->redir_in.quoted_delim = 0;
	/*
	new_size = 0;
	ret = NULL;
	tmp = token;
	while (*tmp)
	{
		if (is_quote(*tmp))
		{
			quote = *tmp;
			start = ++tmp;
		}	
		while (*tmp && tmp != quote)
			token++;
		new_size += token - start;
		ret = ft_realloc_str(ret, new_size);
		ft_strlcat(ret, start, new_size + 1);
		if (tmp == quote)
			++tmp;
	}
	*/
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
	while (is_rediroperator(*token))
		token++;
	while (is_blank(*token))
		token++;
	cmd->redir_in.is_heredoc = 0;
	if (*token == '$' && is_ambiguous_redir(sh, token))
	{
		error_display(token, "ambiguous redirect", 0);
		return (1);
	}
	cmd->redir_in.filename = expand(token, sh);
	return(check_access(cmd->redir_in.filename, F_OK | R_OK));
}

t_bool	set_redirections(t_sh *sh, t_cmd *cmd, char *token)
{
	t_bool	ret;

	ret = 0;
	if (!ft_strncmp(token, "<<", 2))
		ret = set_redir_heredoc(sh, cmd, token);
	else if (!ft_strncmp(token, "<", 1))
		ret = set_redir_infile(sh, cmd, token);
	else if (!ft_strncmp(token, ">>", 2))
		ret = set_redir_append(sh, cmd, token);
	else if (!ft_strncmp(token, "<", 1))
		ret = set_redir_outfile(sh, cmd, token);
	return (ret);
}