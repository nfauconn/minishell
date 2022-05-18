/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:08:30 by user42            #+#    #+#             */
/*   Updated: 2022/05/18 15:23:17 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_input
{
	char	*line_read;
	int		type;
	t_list	*token_list;
}	t_input;

/* CHAR CHECK */
int			is_blank(int c);
int			is_meta(int c);
int			is_quote(int c);

/* TOKENIZER */
void		add_token_to_list(t_list **token_list, char *token);
void		display_token_list(void *content);
void		tokenizer(t_input *input, char *line);

/* LEXER */
void		lexer(t_input *input, t_list *tokens);

#endif