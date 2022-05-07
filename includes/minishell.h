/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/07 17:40:55 by nfauconn         ###   ########.fr       */
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
	char	*cmd;
	char	**args;
	int		is_stdin_redir;
	char	*stdin_file;
	int		is_stdout_redir;
	char	*stdout_file;

}	t_input;

void	end(t_input *input);
char	**tokenized_cmd(t_input *input, char *cmd);

#endif