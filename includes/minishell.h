/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/11 17:29:59 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "builtins.h"
# include "extern_libs.h"
# include "ft_printf.h"
# include "libft.h"
# include "signals.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define QUOTE 34
# define DOUBLE_QUOTE 39

typedef struct s_input
{
	char	*line_read;
	t_list	*token_line;
}	t_input;

void	end(t_input *input);
void	init(t_input *input);
void	tokenize_input(t_input *input, char *line);
//char	**tokenized_cmd(t_input *input, char *cmd);

#endif