/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/11 19:36:11 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
}

static void	find_end(char **s)
{
	while (**s && (**s != '|') && !ft_is_whitespace(**s) && !ft_is_quote(**s))
		(*s)++;
	if (ft_is_quote(**s))
	{
		/*  tmp = *s (to keep the address of exploring start)
			is closing quote ? 
			> yes -> end = after this quote
			> no -> 
		*/
	}
}

static void	find_start(char **s)
{
	while (ft_is_whitespace(**s))
		(*s)++;
}

static void	display_list(void *content)
{
	printf("|%s| ", (char *)content);
}

void	tokenize_input(t_input *input, char *line)
{
	char	*start;
	char	*end;
	char	*token;
	t_list	*new;

	while (*line)
	{
		find_start(&line);
		if (*line == '\0')
			break ;
		start = line;
		find_end(&line);
		end = line;
		token = ft_substr(start, 0, end - start);
		if (token)
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&input->token_line, new);
		}
	}
	ft_lstiter(input->token_line, display_list);
	printf("\n");
}

/* 	

static void	one_token()
{
	char	*token;
	t_list	*new;

	token = ft_substr(jefheri);
	new = lst_new(token);
	ft_lst_add_back(input->token_line, new);
}	

void	tokenize_input
{	
	while (*line)
	{
		while (line = whitespace)
			line++;
		if (line)
		{
			- QUOTE
			- caracteres --> avancer jusqua - whitespace ou /0 ou '|'= END OF TOKEN
											- quote -->

											
		}
		
	}
}
 */