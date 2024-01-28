/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:24:41 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/04 17:13:25 by mdankou          ###   ########.fr       */
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
		while (*token
			&& !((!quote && is_quote(*token)) || (quote && quote == *token)))
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

t_bool	heredoc_set(t_sh *sh, t_cmd *cmd, char *token)
{
	char	*delim;
	char	*hdoc_path;
	t_bool	ret;

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
	hdoc_path = cmd->redir_in.filename;
	ret = run_heredoc(sh, hdoc_path, delim, cmd);
	free(delim);
	return (ret);
}
