/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:35:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 23:46:30 by nfauconn         ###   ########.fr       */
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
bool	set_redirections(t_sh *sh, t_cmd *cmd, char *token);
bool	check_access(char *filename, int flag);
bool	heredoc_set(t_sh *sh, t_cmd *cmd, char *token);
bool	run_heredoc(t_sh *sh, char *heredoc_path, char *delim, bool quoted);
bool	wait_heredoc(void);

/* UTILS */
bool	check_ambig(t_sh *sh, char *token);

/* EXEC_PART */
bool	dup_io_pipeline(t_sh *sh, t_cmd *cmd, int p[2], int fd_in);
bool	dup_io_singlecmd(t_cmd *cmd);
bool	open_redir(t_cmd *cmd);

/* UTILS */
void	close_if_opened(int fd);
void	dup2_close_old(int old_fd, int new_fd);

#endif