/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:35:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 22:39:42 by nfauconn         ###   ########.fr       */
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
t_bool	set_redirections(t_sh *sh, t_cmd *cmd, char *token);
t_bool	check_access(char *filename, int flag);
t_bool	heredoc_set(t_sh *sh, t_cmd *cmd, char *token);
t_bool	run_heredoc(t_sh *sh, char *heredoc_path, char *delim, t_bool quoted);
t_bool	wait_heredoc(void);

/* UTILS */
t_bool	is_ambiguous_redir(t_sh *sh, char *token);

/* EXEC_PART */
t_bool	pipeline_redir(t_sh *sh, t_cmd *cmd, int p[2], int fd_in);
int		single_cmd_redir(t_cmd *cmd);
int		open_redir(t_cmd *cmd);

/* UTILS */
void	close_if_opened(int fd);
void	dup2_close_old(int old_fd, int new_fd);

#endif