/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/12 17:48:56 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
}

static int	quote_is_surrounding_next_word(char **s, char quote)
{
	while (**s && **s != '$' && !ft_is_whitespace(**s) )
	{
		(*s)++;
		if (**s == quote)
			return (1);
	}
	return (0);
}

static int	find_closing_quote(char **s, char quote)
{
	char	*tmp;

	(*s)++;
	while (**s)
	{
		if (**s == quote)
		{
			/*
			** go forward *s while **s != '|' to find the same quote /!\
			** if this is a quote surrounding a word with no whitespaces (OR METACHAR !!!!!!!!!!! $ en tout cas) 
			** 	> continue to search a closing quote
			** else
			** 	> go back to the found quote and return (1);
			*/
			tmp = (*s);
			if (!quote_is_surrounding_next_word(s, quote)) //return a pointer to the location / NULL if didnt found ? maybe easier to use
			{
				(*s) = tmp;
				return (1);
			}
		}
		(*s)++;
	}
	return (0);
}

static void	find_end(char **s)
{
	char	*tmp;

	while (**s && (**s != '|') && !ft_is_whitespace(**s))
	{
		if (ft_is_quote(**s))
		{
			/*  tmp = *s (to keep the address in case no closing quote : restart the exploring)
				> if found same quote -> return ; (because end of token is found)
				> if didnt -> *s = tmp ; (*s)++; continue to search a whitespace to end token
			*/
			tmp = (*s);
			if (find_closing_quote(s, **s))
				return ;
			else
				(*s) = tmp;
		}
		(*s)++;
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
		printf("end = |%c|\n", *line);
		token = ft_substr(start, 0, end - start + 1);
		if (token)
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&input->token_line, new);
		}
	}
	ft_lstiter(input->token_line, display_list);
	printf("\n");
}
