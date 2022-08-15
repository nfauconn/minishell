/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/15 22:27:34 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define B_BLUE "\e[1;30m"
# define B_RED "\e[1;31m"
# define B_GREEN "\e[1;32m"
# define B_YELLOW "\e[1;33m"
# define B_MAGENTA "\e[1;34m"
# define B_CYAN "\e[1;36m"
# define NEUTRAL "\e[0m"

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
char	*build_prompt(void);
char	*get_input(t_sh *sh);
void	redisplay_prompt(void);

#endif