/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/10 13:07:52 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "builtins.h"
# include "defines.h"
# include "execute.h"
# include "extern_libs.h"
# include "ft_printf.h"
# include "libft.h"
# include "signals.h"

typedef struct s_input
{
	char	*line_read;
	t_list	*token_list;
}	t_input;

typedef struct s_cmd
{
	char			**cmd_tab;
	int				redir[2];
	int				in_redir_type;
	int				out_redir_type;
/* 	char			*infile_path;
	char			*outfile_path; */
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	size_t		cmd_nb;
	t_cmd		*cmd_list;
	t_list		*env;
}	t_sh;

/* INIT */
void	init_input(t_input *input);
char	*get_input(void);
void	init_sh(t_sh *sh, char **env);

/* PARSING_TOKENIZER */
int		is_blank(int c);
int		is_redir(int c);
int		is_redir_path(int c);
int		is_separator(int c);
int		is_quote(int c);
void	add_token_to_list(t_list **token_list, char *token);
void	display_token_list(void *content);
int		tokenizer(t_input *input, char *line);
void	set_types_to_expand(t_list *token);
void	complete_types(t_list *token);

/* PARSING_LEX_PARSE */
int		lexer(t_list *tokens);
int		lex_error(char *s);

size_t	get_cmd_nb(t_list *token);
size_t	get_cmd_tab_sz(t_list *token);
int		parser(t_input *input, t_sh *sh);
char	*token_expand(t_list *token_list, t_list *env);

/* END */
void	end(t_input *input, t_sh *sh);
void	end_input(t_input *input);
void	end_sh(t_sh *sh);
void	perror_and_free(t_input *input, char *s);

#endif