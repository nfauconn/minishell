/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:35:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/20 17:23:56 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "extern_libs.h"
# include "structs.h"
# include "error.h"
# include "parsing.h"
# include "exec.h"
# include "signals.h"

#define HEREDOC_NBL_PATH "/tmp/.here_doc_nblines"

/* PARSING__PART */
void	fill_cmd_redir(t_sh *sh, t_list *token, t_cmd *cmd);
void	run_heredoc(t_sh *sh, char *heredoc_path, char *delim);

/* PIPELINE */
void	pipeline_redir(t_sh *sh, t_cmd *cmd, int p[2], int fd_in);

/* SINGLE CMD / BUILTIN */
void	single_cmd_redir(t_sh *sh, t_cmd *cmd);
int	open_single_cmd_redir(t_cmd *cmd);

/* UTILS */
int		open_w_err_check(int fd, char *file_path, int flag);
void	close_if_no_std(int fd);
void	dup2_close_old(int old_fd, int new_fd);

#endif