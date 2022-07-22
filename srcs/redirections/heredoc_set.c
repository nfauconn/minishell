/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:24:41 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/23 01:04:15 by nfauconn         ###   ########.fr       */
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

static char	*get_heredoc_delim(t_list **token, t_cmd *cmd)
{
	char	*delim;

	delim = ft_strdup((char *)(*token)->content);
	while ((*token)->next && ((*token)->next->type == HEREDOC_DELIM
			|| (*token)->next->type == QUOTED_HEREDOC_DELIM))
	{
		if ((*token)->type == QUOTED_HEREDOC_DELIM
			|| (*token)->next->type == QUOTED_HEREDOC_DELIM)
			cmd->delim_quote = 1;
		(*token) = (*token)->next;
		ft_strfjoin(&delim, (char *)(*token)->content);
	}
	return (delim);
}

void	heredoc_set(t_sh *sh, t_list **token, t_cmd *cmd)
{
	char	*delim;

	if (cmd->infile_name)
	{
		if (cmd->heredoc_infile)
			unlink(cmd->infile_name);
		ft_strdel(&cmd->infile_name);
	}
	sh->heredoc_nb++;
	cmd->infile_name = get_heredoc_path(sh->heredoc_nb);
	delim = get_heredoc_delim(token, cmd);
	run_heredoc(sh, cmd->infile_name, delim, cmd->delim_quote);
	free(delim);
}
