/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/08 13:25:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "extern_libs.h"
# include "structs.h"
# include "parsing.h"
# include "exec.h"
# include "builtins.h"
# include "signals.h"
# include "error.h"

/* INIT */
int		init_input(t_sh *sh, t_input *input);
char	*get_input(t_sh *sh);
void	init_sh(t_sh *sh, char **env_sh);

/* END */
void	clear(t_input *input, t_sh *sh);
void	clear_input(t_input *input);
void	clear_sh(t_sh *sh);
void	exit_clear(t_sh *sh);

#endif