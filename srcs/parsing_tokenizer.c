/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/25 16:45:50 by nfauconn         ###   ########.fr       */
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
	char	found_c;
	char	*tmp;

	if (is_quote(**s) && (*((*s) + 1)))
	{
		tmp = (*s)++;
		if (find_closing_quote(s, *tmp))
			return (*s);
		*s = tmp;
	}
	if (is_meta(**s))
	{
		found_c = **s;
		while (**s == found_c)
			(*s)++;
		return (*s);
	}
	(*s)++;
	if (**s == '\0' || is_blank(**s) || is_quote(**s) || is_meta(**s))
		return (*s);
	find_end(s);
	return (*s);
}

static char	*find_start(char **s)
{
	while (is_blank(**s))
		(*s)++;
	return (*s);
}

t_list	*tokenizer(char *line)
{
	char	*start;
	char	*end;
	char	*token;
	t_list	*token_list;

	signal_catching_mode(PGM_EXEC);
	token_list = NULL;
	while (*line)
	{
		start = find_start(&line);
		if (*start == '\0')
			break ;
		else
		{
			end = find_end(&line);
			token = ft_substr(start, 0, end - start);
			add_token_to_list(&token_list, token);
		}
		if (is_blank(*line))
		{
			token = ft_strdup(" ");
			add_token_to_list(&token_list, token);
		}
		start = NULL;
		end = NULL;
	}
	return (token_list);
}
