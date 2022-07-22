/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:11:35 by user42            #+#    #+#             */
/*   Updated: 2022/07/23 00:16:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define BLANK 32
# define QUOTE 39
# define DB_QUOTE 34
# define PIPE 124
# define WORD 131
# define INFILE_NAME 133
# define OUTFILE_NAME 134
# define HEREDOC_DELIM 135
# define QUOTED_HEREDOC_DELIM 137
# define APPEND_OUTFILE_NAME 136

# include "extern_libs.h"
# include "structs.h"
# include "builtins.h"
# include "error.h"

/* TOKENIZER */
int		tokenizer(t_input *input, char *line);
void	add_token_to_list(t_list **token_list, char *token);
void	display_token_list(t_list *lst);
t_list	*skip_token(t_list *token, int to_skip);

/* COMPARISON */
int		is_outfilename(int c);
int		is_rediroperator(int c);
int		is_filename(int c);
int		is_sep(int c);
int		is_dollar_quote(t_list *token);
int		is_metacharacter(int c);
int		is_builtin(char *cmd_name);
int		is_relative_path(char *filename);

/* LEX */
int		lexer(t_list *tokens);
int		lex_error(char *s);

/* TYPES */
void	set_token_types(t_list *token);
t_list	*set_next_words_type(t_list *token, int type);

/* EXPAND */
char	*expand_string(char *ptr, t_sh *sh);
void	token_expand(t_list *token_list, t_sh *sh);
char	*var_value(char *str, size_t len, t_list *env);
void	add_until_var(char **buf, char **ptr, char *start);
void	add_expanded_var(char **buf, char **ptr, t_sh *sh);
char	*get_last_status(t_sh *sh);
t_list	*set_delim_type(t_list *token);
char	*var_value(char *str, size_t len, t_list *env);

/* PARSER */
int		parsing(t_sh *sh, t_input *input);
size_t	get_cmd_nb(t_list *token);
size_t	get_cmd_args_sz(t_list *token);
void	token_to_cmd_lst(t_sh *sh, t_list *token);
t_cmd	*create_new_cmd(t_sh *sh, t_list *token);
void	add_cmd_to_list(t_cmd **head, t_cmd *new);

#endif
