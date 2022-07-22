/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:07:25 by user42            #+#    #+#             */
/*   Updated: 2022/07/22 22:28:20 by nfauconn         ###   ########.fr       */
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
	int				redir_out_type;
	char			*infile_name;
	t_bool			heredoc_infile;
	t_bool			delim_quote;
	char			*outfile_name;
	char			*access_error;
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