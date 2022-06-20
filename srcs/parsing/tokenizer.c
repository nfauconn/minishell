/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/20 18:10:56 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_closing_quote(char **s, char quote)
{
	while (**s)
		if (*((*s)++) == quote)
			return (*s);
	return (NULL);
}

static char	*find_end(t_input *input, char **s)
{
	char	*tmp;

	if (**s == '$' && (!is_blank(*((*s) + 1)) || is_quote(*((*s) + 1))))
		(*s)++;
	if (is_quote(**s))
	{
		tmp = (*s)++;
		if (find_closing_quote(s, *tmp))
			return (*s);
		perror_and_free(input, "minish does not handle non closed quotes");
		return (NULL);
	}
	if (is_separator(**s) || is_redir(**s))
	{
		tmp = *s;
		while (**s == *tmp)
			(*s)++;
		if ((*s) - tmp == 3 && *tmp == '<')
		{
			perror_and_free(input, "minish does not handle here words");
			return (NULL);
		}
		if ((*s) - tmp == 2 && *tmp == '|')
		{
			perror_and_free(input, "minish does not handle double pipes");
			return (NULL);			
		}
		return (*s);
	}
	(*s)++;
	if (**s == '\0' || is_blank(**s) || is_quote(**s) || is_separator(**s) || is_redir(**s))
		return (*s);
	find_end(input, s);
	return (*s);
}

static char	*find_start(char **s)
{
	while (is_blank(**s))
		(*s)++;
	return (*s);
}

int	tokenizer(t_input *input, char *line)
{
	char	*start;
	char	*end;
	char	*token;

	input->token_list = NULL;
	if (!line)
		return(exec_error("no_line\n", ""));
	while (*line)
	{
		start = find_start(&line);
		if (*start == '\0')
			break ;
		else
		{
			end = find_end(input, &line);
			if (end == NULL && line)
				return (FAILURE);
			token = ft_substr(start, 0, end - start);
			add_token_to_list(&input->token_list, token);
		}
		if (is_blank(*line) && !is_separator(*token) && !is_redir(*token))
		{
			token = ft_strdup(" ");
			add_token_to_list(&input->token_list, token);
		}
	}
	ft_lstiter(input->token_list, display_token_list);
	set_types_to_expand(input->token_list);
	return (SUCCESS);
}
