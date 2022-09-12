/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:28:23 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 18:30:43 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_bool	add_redir_in(t_redir **redir_in, char *filename, t_bool is_heredoc)
{
	if (*redir_in)
		clear_redir_in(redir_in);
	*redir_in = (t_redir *)malloc(sizeof (t_redir));
	if (!*redir_in)
		return (error_display("redir_set.c", "malloc internal error", 0));
	(*redir_in)->filename = filename;
	(*redir_in)->fd = NO_REDIR;
	(*redir_in)->is_heredoc = is_heredoc;
	(*redir_in)->heredoc_ctrlc = 0;
	(*redir_in)->quoted_delim = 0;
	(*redir_in)->next = NULL;
	return (0);
}

t_bool	add_redir_out(t_redir **redirout_list, char *filename, t_bool is_append)
{
	t_redir	*redir_out;
	t_redir	*tmp;

	redir_out = (t_redir *)malloc(sizeof (t_redir));
	if (!redir_out)
		return (error_display("redir_set.c", "malloc internal error", 0));
	redir_out->filename = filename;
	redir_out->fd = NO_REDIR;
	redir_out->fd = 0;
	redir_out->is_append = is_append;
	redir_out->next = NULL;
	if (!*redirout_list)
		*redirout_list = redir_out;
	else
	{
		tmp = *redirout_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir_out;
	}
	return (0);
}

static t_bool	set_redir_out(t_sh *sh, t_cmd *cmd, char *token, t_bool append)
{
	char	*filename;

	while (is_redir(*token))
		token++;
	while (is_blank(*token))
		token++;
	if (*token == '$' && check_ambig(sh, token))
		return (error_display(token, "ambiguous redirect", 0));
	filename = expand(token, sh);
	if (filename && *filename
		&& add_redir_out(&cmd->redir_out,  filename, append) == 0)
		return (0);
	else if (filename && !*filename)
		error_display("", "No such file or directory", 0);
	return (1);
}

static t_bool	set_redir_in(t_sh *sh, t_cmd *cmd, char *token, t_bool hdc)
{
	char	*filename;

	while (is_redir(*token))
		token++;
	while (is_blank(*token))
		token++;
	if (hdc)
		return (heredoc_set(sh, cmd, token));
	if (*token == '$' && check_ambig(sh, token))
		return (error_display(token, "ambiguous redirect", 0));
	filename = expand(token, sh);
	if (filename && *filename && add_redir_in(&cmd->redir_in, filename, hdc) == 0)
		return (check_access(cmd->redir_in->filename, F_OK | R_OK));
	else if (filename && !*filename)
		error_display("", "No such file or directory", 0);
	return (1);
}

t_bool	set_redir(t_sh *sh, t_cmd *cmd, char *token)
{
	t_bool	ret;

	ret = 0;
	if (!ft_strncmp(token, "<<", 2))
		ret = set_redir_in(sh, cmd, token, 1);
	else if (!ft_strncmp(token, "<", 1))
		ret = set_redir_in(sh, cmd, token, 0);
	else if (!ft_strncmp(token, ">>", 2))
		ret = set_redir_out(sh, cmd, token, 1);
	else if (!ft_strncmp(token, ">", 1))
		ret = set_redir_out(sh, cmd, token, 0);
	cmd->redir_error = ret;
	return (ret);
}
