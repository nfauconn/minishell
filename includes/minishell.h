/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/01 16:12:26 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "builtins.h"
# include "defines.h"
# include "extern_libs.h"
# include "ft_printf.h"
# include "libft.h"
# include "parsing.h"
# include "signals.h"

typedef struct s_cmd
{
	char			*token;
	int				type;
	int				fd[2];
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	t_cmd	*cmd;
	t_list	*env;
}	t_sh;

void	end(t_input *input, t_sh *sh);
void	end_input(t_input *input);
void	end_sh(t_sh *sh);

t_list	*env_list(char **env);
void	init_sh(t_sh *sh);
void	perror_and_free(t_input *input, char *s);
void	var_expand(t_list *token_list, t_list *env);

#endif