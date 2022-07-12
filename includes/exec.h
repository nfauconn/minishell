/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:22:26 by mdankou           #+#    #+#             */
/*   Updated: 2022/07/12 22:47:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define NO_REDIR -42
# define REDIR_FAIL -1

# define NOT_FOUND 127
# define NOT_EXECUTABLE 126
# define WRONG_REDIR 1
# define EMPTY_CMD 127

# include "extern_libs.h"
# include "structs.h"
# include "builtins.h"
# include "end.h"
# include "error.h"
# include "signals.h"

/* REDIRECTIONS */
void	redir_apply(t_cmd *cmd, int p[2], int fd_in);
void	redir_parse(t_cmd *cmd, t_list *token, t_sh *sh);
void	dup2_close_old(int old_fd, int new_fd);
void	close_if_no_std(int fd);
int		open_w_err_check(int fd, char *file_path, int flag);
char	*run_heredoc(t_sh *sh, char *delim);

/* PATH */
char	*join_path(char const *penv, char const *pexec);
char	**get_path_tab(t_list *env);
char	**get_env_tab(t_list *env);
int		find_path(t_cmd *cmd, char **paths);

/* LAUNCH */
int		launch(t_sh *sh);
int		launch_pipeline(t_sh *sh, t_cmd *cmd);
void	launch_single(t_sh *sh, t_cmd *cmd);
void	cmd_execve(t_sh *sh, t_cmd *cmd);

/* END */
int		wait_children(t_sh *sh);

#endif