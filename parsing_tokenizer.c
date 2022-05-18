/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/18 12:27:52 by user42           ###   ########.fr       */
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

static char	*find_end(char **s)
{
	char	*tmp;

	if (is_quote(**s) && (*((*s) + 1)))
	{
		tmp = (*s)++;
		if (find_closing_quote(s, *tmp))
			return (*s);
		*s = tmp;
	}
	if (**s == IN_REDIR || **s == OUT_REDIR || **s == PIPE)
	{
		(*s)++;
		return (*s);
	}
	(*s)++;
	if (**s == '\0' || ft_iswhitespace(**s) || is_quote(**s)
		|| **s == IN_REDIR || **s == OUT_REDIR || **s == PIPE)
		return (*s);
	find_end(s);
	return (*s);
}

static char	*find_start(char **s)
{
	while (ft_iswhitespace(**s))
		(*s)++;
	return (*s);
}

void	tokenizer(t_input *input, char *line)
{
	char	*start;
	char	*end;
	char	*token;

	signal_catching_mode(PGM_EXEC);
	while (*line)
	{
		start = find_start(&line);
		if (*start == '\0')
			break ;
		else
		{
			end = find_end(&line);
			token = ft_substr(start, 0, end - start);
			add_token_to_list(&input->token_list, token);
		}
		if (ft_iswhitespace(*line))
		{
			token = ft_strdup(" ");
			add_token_to_list(&input->token_list, token);
		}
		start = NULL;
		end = NULL;
	}
	ft_lstiter(input->token_list, display_token_list);
}
