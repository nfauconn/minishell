/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:35:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 17:47:15 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "extern_libs.h"
# include "structs.h"
# include "parse.h"
# include "exec.h"
# include "error.h"

/* PARSING__PART */
t_bool	set_redir(t_sh *sh, t_cmd *cmd, char *token);
t_bool	add_redir_in(t_redir **redirin_list, char *filename, t_bool is_heredoc);
t_bool	check_access(char *filename, int flag);
t_bool	heredoc_set(t_sh *sh, t_cmd *cmd, char *token);
t_bool	run_heredoc(t_sh *sh, char *heredoc_path, char *delim, t_cmd *cmd);
t_bool	wait_heredoc(void);

/* UTILS */
t_bool	check_ambig(t_sh *sh, char *token);

/* EXEC_PART */
t_bool	dup_io_pipeline(t_sh *sh, t_cmd *cmd, int p[2], int fd_in);
t_bool	dup_io_singlecmd(t_cmd *cmd);
t_bool	open_redir(t_cmd *cmd);

#endif