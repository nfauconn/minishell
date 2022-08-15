/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:24:41 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/15 18:14:39 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static char	*get_heredoc_path(int heredoc_nb)
{
	char	*heredoc_path;
	char	*heredoc_no;

	heredoc_no = ft_itoa(heredoc_nb);
	heredoc_path = ft_strjoin("/tmp/.here_doc", heredoc_no);
	free(heredoc_no);
	return (heredoc_path);
}

static char	*get_heredoc_delim(char *token)
{
	char	*start;
	char	quote;
	size_t	new_size;
	char	*delim;

	new_size = 0;
	quote = 0;
	delim = NULL;
	while (*token)
	{
		start = token;
		while (*token &&
			!((!quote && is_quote(*token)) || (quote && quote == *token)))
			token++;
		if (!quote && is_quote(*token))
			quote = *token;
		else if (quote && quote == *token)
			quote = 0;
		new_size += token - start;
		delim = ft_reallocstr(delim, new_size);
		ft_strlcat(delim, start, new_size + 1);
		if (is_quote(*token))
			start = ++token;
	}
	return (delim);
}

bool	heredoc_set(t_sh *sh, t_cmd *cmd, char *token)
{
	char	*delim;
	bool	ret;

	ret = 0;
	if (cmd->redir_in.filename)
	{
		if (cmd->redir_in.is_heredoc)
			unlink(cmd->redir_in.filename);
		ft_strdel(&cmd->redir_in.filename);
	}
	sh->heredoc_nb++;
	cmd->redir_in.filename = get_heredoc_path(sh->heredoc_nb);
	delim = get_heredoc_delim(token);
	if (run_heredoc(sh, cmd->redir_in.filename, delim, cmd->redir_in.quoted_delim))
		ret = 1;
	free(delim);
	return (ret);
}