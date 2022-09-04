/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:07:25 by user42            #+#    #+#             */
/*   Updated: 2022/09/04 17:54:10 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "extern_libs.h"

enum
{
	cd = 0,
	echo,
	env,
	exit2,
	export,
	pwd,
	unset,
};

typedef struct s_input
{
	char	*line_read;
	t_list	*token_list;
}	t_input;

typedef struct s_redir
{
	char	*filename;
	char	*delim;
	int		fd;
	t_bool	is_heredoc;
	t_bool	heredoc_ctrlc;
	t_bool	quoted_delim;
	t_bool	is_append;
}	t_redir;

typedef struct s_cmd
{
	size_t			index;
	int				built_i;
	char			**args;
	t_redir			redir_in;
	t_redir			redir_out;
	t_bool			redir_error;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	size_t			level;
	size_t			line_nb;
	size_t			cmd_nb;
	t_cmd			*cmd_list;
	int				heredoc_nb;
	t_list			*env;
	int				(*exec_built[7])(struct s_sh *, t_cmd *);
}	t_sh;

#endif