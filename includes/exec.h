/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:22:26 by mdankou           #+#    #+#             */
/*   Updated: 2022/07/30 01:06:44 by user42           ###   ########.fr       */
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
# define NO_SUCH_FILE 127
# define IS_DIR 126
# define NO_ACCESS_RIGHTS 126

# include "extern_libs.h"
# include "structs.h"
# include "builtins.h"
# include "redir.h"
# include "error.h"
# include "exit.h"
# include "signals.h"

/* PATH */
char	*join_path(char const *penv, char const *pexec);
char	**get_path_tab(t_list *env);
char	**get_env_tab(t_list *env);
int		find_path(t_cmd *cmd, char **paths);

/* LAUNCH */
void	launch(t_sh *sh);
int		launch_pipeline(t_sh *sh, t_cmd *cmd);
void	launch_forked_builtin(t_sh *sh, t_cmd *cmd);
void	launch_single(t_sh *sh, t_cmd *cmd);
void	launch_single_builtin(t_sh *sh, t_cmd *cmd);
void	cmd_execve(t_sh *sh, t_cmd *cmd);

/* END */
void	wait_children(t_sh *sh);
void	wait_child(size_t cmd_nb, size_t cmd_index);
void	wait_heredoc(void);

#endif