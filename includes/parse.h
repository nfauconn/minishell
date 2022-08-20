/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:11:35 by user42            #+#    #+#             */
/*   Updated: 2022/08/06 21:42:18 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define QUOTE 39
# define DB_QUOTE 34

# include "extern_libs.h"
# include "structs.h"
# include "redir.h"
# include "error.h"

t_bool		parse(t_sh *sh, t_input *input);

/* TOKENIZER */
t_bool		tokenize(t_input *input);
t_bool		tokenize_redir(char **s);
t_bool		go_through_same_char(char **s);
t_bool		check_closing_quote(char **s, char quote);
void		add_token_to_list(t_list **token_list, char *token);
void		display_token_list(t_list *lst);
void		skip_token(t_list **token, int to_skip);

/* CHAR_COMPAR */
t_bool		is_operator(char c);
t_bool		is_redir(char c);
t_bool		is_sep_operator(char c);
t_bool		is_metachar(char c);
t_bool		is_doll_then_quote(char *s);

/* STR COMPAR */
char		*contains_quotes(char *str);
char		*contains_blanks(char *str);

/* FILE_COMPAR */
t_bool		is_infilename(int c);
t_bool		is_heredoc_delim(int c);
t_bool		is_outfilename(int c);
t_bool		is_filename(int c);
t_bool		is_dollar_quote(t_list *token);
t_bool		is_builtin(char *cmd_name);
t_bool		is_absolute_path(char *filename);

/* LEX */
t_bool		lexer(t_list *tokens);
t_bool		lex_perror(char *s);

/* CMD_LIST_BUILD */
t_bool		build_cmd_lst(t_sh *sh, t_list *token);
t_cmd		*build_cmd(t_sh *sh, t_list *token, size_t i);
t_cmd		*cmd_init(void);
t_bool		set_cmd_params(t_sh *sh, t_list *token, t_cmd *cmd);
void		add_cmd_to_list(t_cmd **head, t_cmd *new);

/* CMD_BUILD_UTILS */
void		clear_tab(char **tab, int index);
size_t		get_args_nb(t_list *token);
size_t		arg_len(char *s);

/* EXPAND */
char		*expand(char *ptr, t_sh *sh);
void		escape_quotes(char *str);
char		*expand_str(char *ptr, size_t len, t_sh *sh);
char		*expand_var(char **s, t_sh *sh);
char		*var_value(char *ptr, size_t len, t_list *env);

/* QUOTE_REMOVAL */
char		*remove_quote(char *str);

/* DEBUG */
void		print_token_list(t_input *input);
void		print_commands(t_sh *sh);

#endif
