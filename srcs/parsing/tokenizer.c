/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/21 13:29:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*end_of_sep_or_redir(t_input *input, char *s)
{
	char	*tmp;

	tmp = *s;
	while (*s == *tmp)
		s++;
	if (s - tmp == 3 && *tmp == '<')
		return (perror_and_free(input, "does not handle here words"));
	if (s - tmp == 2 && *tmp == '|')
		return(perror_and_free(input, "does not handle double pipes"));
	return (s);
}

static char	*find_closing_quote(t_input *input, char *s, char quote)
{
	s++;
	while (*s)
	{
		if (*(s++) == quote)
			return (s);
	}
	return (perror_and_free(input, "does not handle non closed quotes"));
}

static char	*find_end(t_input *input, char *s)
{
	while (*s && !is_blank(*s))
	{
		if (*s == '$' && is_quote(*(s + 1)))
			s++;
		if (is_quote(*s))
			return (find_closing_quote(input, s, *s));
		if (is_separator(*s) || is_redir(*s))
			return (end_of_sep_or_redir(input, s));
		s++;
	}
	return (s);
}

static char	*find_start(char *s)
{
	while (is_blank(*s))
		s++;
	return (s);
}

int	tokenizer(t_input *input, char *line)
{
	char	*start;
	char	*token;

	while (line && *line)
	{
		start = find_start(line);
		if (*start == '\0')
			break ;
		else
		{
			line = find_end(input, start);
			if (!input->line_read)
				return (FAILURE);
			printf("line = %s\n", line);
			token = ft_substr(start, 0, line - start);
			add_token_to_list(&input->token_list, token);
		}
		if (line && is_blank(*line) && !is_redir(*token))
		{
			token = ft_strdup(" ");
			add_token_to_list(&input->token_list, token);
			line++;
		}
	}
	return (SUCCESS);
}
