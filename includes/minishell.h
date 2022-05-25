/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/25 15:16:11 by nfauconn         ###   ########.fr       */
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

typedef struct s_sh
{
	t_list	*env;
}	t_sh;

void	end(t_input *input);
t_list	*env_list(char **env);
void	init_sh(t_sh *sh);
void	perror_and_free(t_input *input, char *s);

#endif