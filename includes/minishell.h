/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/08 14:47:38 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define B_BLUE "\001\e[1;30m\002"
# define B_RED "\001\e[1;31m\002"
# define B_GREEN "\001\e[1;32m\002"
# define B_YELLOW "\001\e[1;33m\002"
# define B_MAGENTA "\001\e[1;34m\002"
# define B_CYAN "\001\e[1;36m\002"
# define NEUTRAL "\001\e[0m\002"

# include "extern_libs.h"
# include "structs.h"
# include "parse.h"
# include "exec.h"
# include "reset.h"
# include "signals.h"
# include "error.h"

/* INIT */
void	init_sh(t_sh *sh);
t_list	*init_env(char **env_tab);

/* PROMPT LOOP */
int		init_input(t_sh *sh, t_input *input);
char	*build_prompt(t_list *env);
char	*get_input(t_sh *sh);
void	redisplay_prompt(void);

#endif