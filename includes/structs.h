/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:07:25 by user42            #+#    #+#             */
/*   Updated: 2022/07/08 13:26:18 by user42           ###   ########.fr       */
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

#endif