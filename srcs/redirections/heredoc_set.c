/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:24:41 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/11 21:18:31 by nfauconn         ###   ########.fr       */
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
	char	*delim;

	while (is_rediroperator(*token))
		token++;
	while (is_blank(*token))
		token++;
	delim = ft_strdup(token);
	return (delim);
}

t_bool	heredoc_set(t_sh *sh, t_cmd *cmd, char *token)
{
	char	*delim;
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
	if (run_heredoc(sh, cmd->redir_in.filename, delim, cmd->redir_in.quoted_delim))
		ret = 1;
	free(delim);
	return (ret);
}
