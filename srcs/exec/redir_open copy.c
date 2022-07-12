/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:20:37 by mdankou           #+#    #+#             */
/*   Updated: 2022/07/09 18:42:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"


static void	set_redir_out(t_cmd *cmd, t_list *token, char *file)
{
	if (cmd->redir_out != NO_REDIR)
		close(cmd->redir_out);
	else if (token->type == APPEND_FILE)
		cmd->redir_out = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (token->type == TRUNC)
		cmd->redir_out = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
}

static void	set_redir_in(t_cmd *cmd, t_list *token, char *file, t_sh *sh)
{
	if (cmd->redir_in != NO_REDIR)
		close(cmd->redir_in);
	else if (token->type == INFILE)
		cmd->redir_in = open(file, O_RDONLY);
	else if (token->type == DELIMITER)
		run_heredoc(&cmd->redir_in, token->content, sh);
}

void	redir_open(t_cmd *cmd, t_list *token, t_sh *sh)
{
	char	*file;

	errno = 0;
	cmd->redir_in = NO_REDIR;
	cmd->redir_out = NO_REDIR;
	while (token && !is_sep(token->type) && !errno)
	{
		file = (char *)token->content;
		if (is_infile(token->type) && cmd->redir_in != WRONG_REDIR)
		{
			set_redir_in(cmd, token, file, sh);
		}
		else if (is_outfile(token->type) && cmd->redir_out != WRONG_REDIR)
		{
			set_redir_out(cmd, token, file);
		}
		if (errno)
			error_display(file, strerror(errno), 0);
		token = token->next;
	}
}
