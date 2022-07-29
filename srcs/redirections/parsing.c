/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:28:23 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/13 20:49:44 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "parsing.h"

static void	set_redir_out(t_sh *sh, t_list *token, t_cmd *cmd, char *file)
{
	(void)sh;
	if (cmd->outfile)
		ft_strdel(&cmd->outfile);
	cmd->redir_in_type = token->type;
	cmd->outfile = ft_strdup(file);
}

static void	set_redir_in(t_sh *sh, t_list *token, t_cmd *cmd, char *file)
{
	char	*heredoc_no;

	if (cmd->infile)
		ft_strdel(&cmd->infile);
	if (token->type == INFILE)
	{
		cmd->redir_in_type = INFILE;
		cmd->infile = ft_strdup(file);
	}
	else if (token->type == DELIMITER)
	{
		cmd->redir_in_type = HEREDOC;
		sh->heredoc_nb++;
		heredoc_no = ft_itoa(sh->heredoc_nb);
		cmd->infile = ft_strjoin("/tmp/.here_doc", heredoc_no);
		ft_strdel(&heredoc_no);
		run_heredoc(sh, cmd->infile, (char *)token->content);
	}
}

void	fill_cmd_redir(t_sh *sh, t_list *token, t_cmd *cmd)
{
	char	*file;
	char	*tmp;

	errno = 0;
	while (token && !is_sep(token->type) && !errno)
	{
		file = (char *)token->content;
		if (is_infile(token->type))
		{
			set_redir_in(sh, token, cmd, file);
			access(cmd->infile, R_OK);
		}
		else if (is_outfile(token->type))
		{
			set_redir_out(sh, token, cmd, file);
		}
		if (errno)
		{
			cmd->redir_error = ft_strjoin(file, ": ");
			tmp = cmd->redir_error;
			cmd->redir_error = ft_strjoin(tmp, strerror(errno));
			free(tmp);
			return ;
		}
		token = token->next;
	}
}
