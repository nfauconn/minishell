/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/12 20:37:42 by nfauconn         ###   ########.fr       */
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
# include "end.h"
# include "error.h"

/* INIT */
int		init_input(t_sh *sh, t_input *input);
char	*get_input(t_sh *sh);
void	init_sh(t_sh *sh, char **env_sh);

#endif