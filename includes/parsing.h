/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:11:35 by user42            #+#    #+#             */
/*   Updated: 2022/07/12 22:25:47 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define BLANK 32
# define QUOTE 39
# define DB_QUOTE 34
# define PIPE 124
# define HEREDOC 129
# define APPEND 130
# define WORD 131
# define INFILE 133
# define TRUNC 134
# define DELIMITER 135
# define APPEND_FILE 136

# include "extern_libs.h"
# include "structs.h"
# include "builtins.h"
# include "error.h"

/* TOKENIZER */
int		tokenizer(t_input *input, char *line);
void	add_token_to_list(t_list **token_list, char *token);
void	display_token_list(t_list *lst);
t_list *skip_token(t_list *token, int to_skip);

/* COMPARISON */
int		is_infile(int c);
int		is_outfile(int c);
int		is_redir(int c);
int		is_redir_path(int c);
int		is_sep(int c);
int		is_dollar_quote(t_list *token);
int		is_word(int c);
int		is_builtin(char *cmd_name);

/* TYPES */
void	set_types_for_lex(t_list *token);
void	complete_types(t_list *token);

/* LEX */
int		lexer(t_list *tokens);
int		lex_error(char *s);

/* EXPAND */
char	*expand_string(char *ptr, t_sh *sh);
void	token_expand(t_list *token_list, t_sh *sh);
char	*var_value(char *str, size_t len, t_list *env);
void	add_until_var(char **buf, char **ptr, char *start);
void	add_expanded_var(char **buf, char **ptr, t_sh *sh);
char	*get_last_status(t_sh *sh);

/* PARSER */
int		parsing(t_sh *sh, t_input *input);
size_t	get_cmd_nb(t_list *token);
size_t	get_cmd_args_sz(t_list *token);
void	token_to_cmd_lst(t_sh *sh, t_list *token);
t_cmd	*create_new_cmd(t_sh *sh, t_list *token);
void	conv_redir(t_sh *sh, t_list *token, t_cmd *cmd);
void	add_cmd_to_list(t_cmd **head, t_cmd *new);

#endif
