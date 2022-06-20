/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/20 12:15:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "builtins.h"
# include "defines.h"
# include "exec.h"
# include "extern_libs.h"
# include "ft_printf.h"
# include "libft.h"
# include "signals.h"

//#define DEBUG

typedef struct s_input
{
	char	*line_read;
	t_list	*token_list;
}	t_input;

typedef struct s_sh
{
	size_t		cmd_nb;
	t_cmd		*cmd_list;
	t_list		*env;
	size_t		error_status;
}	t_sh;

/* INIT */
int	init_input(t_input *input);
char	*get_input(void);
void	init_sh(t_sh *sh, char **env);

/* PARSING_TOKENIZER */
int		is_blank(int c);
int		is_in_redir_path(int c);
int		is_out_redir_path(int c);
int		is_redir(int c);
int		is_redir_path(int c);
int		is_separator(int c);
int		is_quote(int c);
void	add_token_to_list(t_list **token_list, char *token);
void	display_token_list(void *content);
int		tokenizer(t_input *input, char *line);
void	set_types_to_expand(t_list *token);
void	complete_types(t_list *token);

/* PARSING_LEX */
int		lexer(t_list *tokens);
int		lex_error(char *s);

/* PARSING_PARSER */
int		parser(t_input *input, t_sh *sh);
void	token_expand(t_list *token_list, t_list *env);

/*EXECUTE*/
int		cmd_execute(t_sh *sh);

/* PARSING_CONV_TO_CMD */
size_t	get_cmd_nb(t_list *token);
size_t	get_cmd_args_sz(t_list *token);
void	add_cmd_to_list(t_cmd **head, t_cmd *new);
t_cmd	*create_new_cmd(t_list *token);
void	token_to_cmd_lst(t_sh *sh, t_list *token);

/* END */
void	end(t_input *input, t_sh *sh);
void	end_input(t_input *input);
void	end_sh(t_sh *sh);
void	perror_and_free(t_input *input, char *s);
void	error_display(char *s1, char *s2);
int		wait_children(t_sh *sh);

#endif