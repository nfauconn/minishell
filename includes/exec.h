/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:22:26 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/29 20:23:39 by user42           ###   ########.fr       */
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

void	(*exec_built[6])(t_sh *sh, t_cmd *cmd);
int		mini_cd(t_sh *sh, t_cmd *cmd);
int		mini_echo(t_sh *sh, t_cmd *cmd);
int		mini_env(t_sh *sh, t_cmd *cmd);
int		mini_export(t_sh *sh, t_cmd *cmd);
int		mini_pwd(t_sh *sh, t_cmd *cmd);
int		mini_unset(t_sh *sh, t_cmd *cmd);


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