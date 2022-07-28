/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/28 09:35:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "extern_libs.h"
# include "structs.h"
# include "parsing.h"
# include "redir.h"
# include "exec.h"
# include "signals.h"
# include "clearexit.h"
# include "error.h"

void	init_sh(t_sh *sh, char **env_sh);
int		init_input(t_sh *sh, t_input *input);
char	*get_input(t_sh *sh);

void	reset_for_new_input(t_sh *sh, t_input *input);
void	redisplay_prompt(void);

#endif