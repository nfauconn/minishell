/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/06 21:43:45 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define MINISH_COLOR "\e[1;35m"
#define DIRS_COLOR "\e[1;36m"
#define INPUT_COLOR "\e[0m"

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