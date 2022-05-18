/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/18 12:42:55 by user42           ###   ########.fr       */
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

typedef struct s_input
{
	char	*line_read;
	int		type;
	t_list	*token_list;
}	t_input;

void	end(t_input *input);
void	clean_exit(t_input *input, char *s);
void	lexer(t_input *input, t_list *tokens);
void	init(t_input *input);
void	tokenizer(t_input *input, char *line);

#endif