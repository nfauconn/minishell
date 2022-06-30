/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/30 10:03:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# define DEBUG

# include "builtins.h"
# include "defines.h"
# include "exec.h"
# include "extern_libs.h"
# include "ft_printf.h"
# include "libft.h"
# include "signals.h"

typedef struct s_input
{
	char	*line_read;
	t_list	*token_list;
}	t_input;

/* INIT */
int		init_input(t_sh *sh, t_input *input);
char	*get_input(t_sh *sh);
void	init_sh(t_sh *sh, char **env_sh);

/* PARSING_COMPARISON */
int		is_infile(int c);
int		is_outfile(int c);
int		is_redir(int c);
int		is_redir_path(int c);
int		is_sep(int c);
int		is_dollar_quote(t_list *token);
int		is_word(int c);
int		is_builtin(char *cmd_name);

/* PARSING_TOKEN */
void	add_token_to_list(t_list **token_list, char *token);
void	display_token_list(t_list *lst);
int		tokenizer(t_input *input, char *line);
t_list *skip_token(t_list *token, int to_skip);

/* PARSING_TYPES */
void	set_types_for_lex(t_list *token);
void	complete_types(t_list *token);

/* PARSING_LEX */
int		lexer(t_list *tokens);
int		lex_error(char *s);

/* PARSING_PARSER */
int		parsing(t_input *input, t_sh *sh);
char	*expand_string(char *ptr, t_sh *sh);
void	token_expand(t_list *token_list, t_sh *sh);
void	add_until_var(char **buf, char **ptr, char *start);
void	add_expanded_var(char **buf, char **ptr, t_sh *sh);
char	*get_last_status(t_sh *sh);

/* EXECUTE */
int		launch(t_sh *sh);
int		builtin_child(t_sh *sh, t_cmd *cmd);
int		single_builtin_exec(t_sh *sh, t_cmd *cmd);
int		subshells_seq(t_sh *sh, t_cmd*cmd);

/* PARSING_CONV_TO_CMD */
size_t	get_cmd_nb(t_list *token);
size_t	get_cmd_args_sz(t_list *token);
void	add_cmd_to_list(t_cmd **head, t_cmd *new);
t_cmd	*create_new_cmd(t_sh *sh, t_list *token);
void	token_to_cmd_lst(t_sh *sh, t_list *token);

/* END */
void	end(t_input *input, t_sh *sh);
void	end_input(t_input *input);
void	end_sh(t_sh *sh);
char	*perror_and_free(t_input *input, char *s);
void	error_display(char *s1, char *s2);
void	error_exit(char *cmd_name, int8_t error_code);
int		wait_children(t_sh *sh);

#endif