/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/15 16:11:36 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
}

static char	*find_closing_quote(char **s, char quote)
{
	printf("quote = %c\n", quote);
	while (**s)
	{
		if (**s == quote)
			return (*s);
		(*s)++;
	}
	return (NULL);
}

static char	*find_end(char **s)
{
	char	*tmp;

	while (**s && !ft_iswhitespace(**s) && **s != PIPE)
	{
		if (ft_is_quote(**s) && (*((*s) + 1) != '\0'))
		{
			tmp = *s;
			(*s)++;
			*s = find_closing_quote(s, *(*s - 1));
			if (*s)
			{
				(*s)++;
				if (ft_iswhitespace(**s) || **s != PIPE)
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
		if (*line == '\0')
			break ;
		if (*line == PIPE)
		{
			line++;
			token = ft_strdup("|");
		}
		else
		{
			end = find_end(&line);
			token = ft_substr(start, 0, end - start);
		}
		if (token)
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&input->token_line, new);
		}
	}
	ft_lstiter(input->token_line, display_list);
	printf("\n");
}
