/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:08:30 by user42            #+#    #+#             */
/*   Updated: 2022/06/07 18:14:13 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_input
{
	char	*line_read;
	t_list	*token_list;
}	t_input;

/* INIT */
void		init_input(t_input *input);

/* CHAR CHECK */
int			is_blank(int c);
int			is_separator(int c);
int			is_quote(int c);

/* TOKENIZER */
void		add_token_to_list(t_list **token_list, char *token);
void		display_token_list(void *content);
int			tokenizer(t_input *input, char *line);

/* TYPES */
void		get_parsing_types(t_list *token);

/* LEXER */
int		lexer(t_list *tokens);

#endif