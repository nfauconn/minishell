/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:22:26 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/30 09:27:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

enum
{
	cd = 0,
	echo,
	env,
	export,
	pwd,
	unset,
};

typedef struct s_cmd
{
	size_t			index;
	char			*name;
	int				built_i;
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
	int				last_status;
	char			*last_status_str;
	int				(*exec_built[6])(struct s_sh *, t_cmd *);
}	t_sh;

/* BUILTINS */
int		(*exec_built[6])(t_sh *sh, t_cmd *cmd);
int		mini_cd(t_sh *sh, t_cmd *cmd);
int		mini_echo(t_sh *sh, t_cmd *cmd);
int		mini_env(t_sh *sh, t_cmd *cmd);
int		mini_export(t_sh *sh, t_cmd *cmd);
int		mini_pwd(t_sh *sh, t_cmd *cmd);
int		mini_unset(t_sh *sh, t_cmd *cmd);

/* COMMANDS */
int		single_cmd_seq(t_sh *sh, t_cmd *cmd);
int		pipeline_seq(t_sh *sh, t_cmd *cmd);
void	exec_cmd(t_sh *sh, t_cmd *cmd);

/* REDIRECTIONS */
void	redir_apply(t_cmd *cmd, int p[2], int fd_in);
void	redir_open(t_cmd *cmd, t_list *token, t_sh *sh);

char	*join_path(char const *penv, char const *pexec);
char	**get_path_tab(t_list *env);
char	**get_env_tab(t_list *env);
int		find_path(t_cmd *cmd, char **paths);
void	run_heredoc(int *fd, char *delim, t_sh *sh);
int		exec_error(char *s1, char *s2);

/* FILE UTILS */
void	dup2_close_old(int old_fd, int new_fd);
void	close_if_exists(int fd);
int		open_w_err_check(int fd, char *file_path, int flag);
void	pipe_w_err_check(int *redir);

#endif