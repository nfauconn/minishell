/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:07:25 by user42            #+#    #+#             */
/*   Updated: 2022/07/20 17:40:34 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "extern_libs.h"

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
	int				redir_in_type;
	int				redir_out_type;
	int				heredoc_nb;
	char			*infile;
	char			*outfile;
	char			*redir_error;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	size_t			cmd_nb;
	t_cmd			*cmd_list;
	int				heredoc_nb;
	t_list			*env;
	int				last_status;
	char			*last_status_str;
	int				(*exec_built[7])(struct s_sh *, t_cmd *);
}	t_sh;

#endif