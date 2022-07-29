/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/30 00:55:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "extern_libs.h"
# include "structs.h"
# include "parsing.h"
# include "exec.h"
# include "reset.h"
# include "signals.h"
# include "error.h"

/* INIT */
void	init_sh(t_sh *sh);
t_list	*init_env(char **env_tab);

/* PROMPT LOOP */
int		init_input(t_sh *sh, t_input *input);
char	*get_input(t_sh *sh);
void	redisplay_prompt(void);

#endif