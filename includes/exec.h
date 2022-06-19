/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:22:26 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/19 18:51:44 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_cmd
{
	char			**cmd_tab;
	size_t			index;
	int				redir_in;
	int				redir_out;
	int				in_redir_type;
	int				out_redir_type;
	struct s_cmd	*next;
}	t_cmd;

char	*join_path(char const *penv, char const *pexec);
void	clean_string_array(char **array);
char	**get_path_tab(t_list *env);
char	**get_env_tab(t_list *env);
void	cmd_redirections(t_cmd *cmd, t_list *token);
void	run_heredoc(int *fd, char *delim);
int		exec_error(char *s1, char *s2);

/* FILE UTILS */
void	dup2_close_old(int old_fd, int new_fd);
void	close_if_exists(int fd);
int		open_w_err_check(int fd, char *file_path, int flag);
void	pipe_w_err_check(int *redir);

#endif