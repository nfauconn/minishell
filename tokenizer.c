/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/13 11:47:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
}

static int	quote_is_surrounding_next_word(char **s, char quote)
{
	while (**s && **s != '$' && !ft_iswhitespace(**s) )
	{
		if (**s == quote)
			return (1);
		(*s)++;
	}
	return (0);
}

static int	find_closing_quote(char **s, char quote)
{
	char	*tmp;

	while (**s)
	{
		(*s)++;
		if (**s == quote)
		{
			printf("**s (%c) == quote\n", **s);
			/*
			** go forward *s while **s to find the same quote /!\ dont care about pipes in this case because they would not be interpreted if they are btww quotes
			** if this is a quote surrounding a word with no whitespaces (OR METACHAR !!!!!!!!!!! $ en tout cas) 
			** 	> continue to search a closing quote
			** else
			** 	> go back to the found quote and return (1);
			*/
			tmp = (*s);
			(*s)++;
			if (!quote_is_surrounding_next_word(s, quote)) //return a pointer to the location / NULL if didnt found ? maybe easier to use
			{
				printf("quote is not surrounding next word, search for closing quote continues \n");
				(*s) = tmp;
				return (1);
			}
			else
				printf("quote was surrounding next word, here is *s : %s\n", *s);
		}
	}
	return (0);
}

static void	find_end(char **s)
{
	char	*tmp;

	while (**s && (**s != '|') && !ft_iswhitespace(**s))
	{
		if (ft_is_quote(**s))
		{
			/*  tmp = *s (to keep the address in case no closing quote : restart the exploring)
				> if found same quote -> return ; (because end of token is found)
				> if didnt -> *s = tmp ; (*s)++; continue to search a whitespace to end token
			*/
//			printf("found a quote\n");
			tmp = (*s);
			if (find_closing_quote(s, **s))
			{
				printf("found a closing quote\n");
				return ;
			}
			else
				(*s) = tmp;
		}
		else
			(*s)++;
	}
}

static void	find_start(char **s)
{
	while (ft_iswhitespace(**s))
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
		printf("token = |%s|\n", token);
		if (token)
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&input->token_line, new);
		}
	}
	ft_lstiter(input->token_line, display_list);
	printf("\n");
}
