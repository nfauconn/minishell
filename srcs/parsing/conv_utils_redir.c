/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_utils_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:28:23 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/12 21:30:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	set_redir_out(t_sh *sh, t_list *token, t_cmd *cmd, char *file)
{
	(void)sh;
	if (access(file, R_OK) == -1)
		return ;
	if (cmd->redir_out != NO_REDIR)
		ft_strdel(&cmd->outfile);
	cmd->redir_in_type = token->type;
	cmd->outfile = ft_stdrup(file);
}

static void	set_redir_in(t_sh *sh, t_list *token, t_cmd *cmd, char *file)
{
	if (cmd->redir_in != NO_REDIR)
		ft_strdel(&cmd->infile);
	if (token->type == INFILE)
	{
		cmd->redir_in_type = INFILE;
		cmd->infile = ft_stdrup(file);
	}
	else if (token->type == DELIMITER)
	{
		cmd->redir_in_type = HEREDOC;
		run_heredoc(&cmd->redir_in, token->content, sh);
		// cmd->infile = <heredoc_filepath returned by the func>
	}
}

void	conv_redir(t_sh *sh, t_list *token, t_cmd *cmd)
{
	char	*file;

	errno = 0;
	while (token && !is_sep(token->type) && !errno)
	{
		file = (char *)token->content;
		if (is_infile(token->type) && access(file, R_OK) != -1)
		{
			set_redir_in(sh, token, cmd, file);
		}
		else if (is_outfile(token->type) && access(file, W_OK) != -1)
		{
			set_redir_out(sh, token, cmd, file);
		}
		if (errno)
		{
			cmd->redir_error = ft_stdrup(sterror(errno));
			return ;
		}
		token = token->next;
	}
}
