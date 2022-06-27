/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:22:26 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/27 21:47:47 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_cmd
{
	size_t			index;
	char			*name;
	char			**args;
	char			**env;
	char			**env_paths;
	char			*path;
	int				redir_in;
	int				redir_out;	
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	size_t			cmd_nb;
	t_cmd			*cmd_list;
	t_list			*env;
	unsigned char	last_status;
	char			*last_status_str;
}	t_sh;

char	*join_path(char const *penv, char const *pexec);
char	**get_path_tab(t_list *env);
char	**get_env_tab(t_list *env);
int		find_path(t_cmd *cmd, char **paths);
void	cmd_redirections(t_cmd *cmd, t_list *token, t_sh *sh);
void	run_heredoc(int *fd, char *delim, t_sh *sh);
int		exec_error(char *s1, char *s2);

/* FILE UTILS */
void	dup2_close_old(int old_fd, int new_fd);
void	close_if_exists(int fd);
int		open_w_err_check(int fd, char *file_path, int flag);
void	pipe_w_err_check(int *redir);

#endif