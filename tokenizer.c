/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/13 16:28:33 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
}

static int	ft_is_shell_separator(int c)
{
	return (c == '|');
}

static int	quote_is_surrounding_next_word(char **s, char quote)
{
	(*s)++;
	while (**s && **s != '$' && !ft_iswhitespace(**s) )
	{
		if (**s == quote)
			return (1);
		(*s)++;
	}
	return (0);
}

static char	*find_closing_quote(char **s, char quote)
{
	char	*tmp;

	(*s)++;
	while (**s)
	{
		if (**s == quote)
		{
			printf("found quote = %c\n", quote);
			tmp = *s;
			if (!quote_is_surrounding_next_word(s, quote))
			{
				printf("found closing quote\n");
				return (*s);
			}
		}
		(*s)++;
	}
	return (NULL);
}

static char	*find_end(char **s)
{
	char	*tmp;

	while (**s && !ft_is_shell_separator(**s) && !ft_iswhitespace(**s))
	{
		if (ft_is_quote(**s) && (*((*s) + 1) != '\0'))
		{
			tmp = *s;
			if (quote_is_surrounding_next_word(s, **s))
			{
				(*s)++;
				return (*s);
			}
			*s = tmp;
			*s = find_closing_quote(s, **s);
			if (*s)
			{
				(*s)++;
				return (*s);
			}
			else
				*s = tmp;
		}
		(*s)++;
	}
	return (*s);
}

static char	*find_start(char **s)
{
	while (ft_iswhitespace(**s))
		(*s)++;
	return (*s);
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

	signal_catching_mode(PGM_EXEC);
	while (*line)
	{
		start = find_start(&line);
		end = find_end(&line);
		token = ft_substr(start, 0, end - start);
		printf("token = |%s|\n", token);
		if (token)
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&input->token_line, new);
		}
		line++;
//		line += end - start;
	}
	ft_lstiter(input->token_line, display_list);
	printf("\n");
}
