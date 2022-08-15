/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/06 21:43:45 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	find_end(char **s)
{
	if (is_sep_operator(**s))
		return (go_through_same_char(s));
	if (is_redir(**s))
		return (tokenize_redir(s));
	while (**s && !is_operator(**s))
	{
		if (is_quote(**s) && check_closing_quote(s, **s) == FAIL)
			return (1);
		(*s)++;
	}
	return (0);
}

static char	*find_start(char **s)
{
	while (**s && is_blank(**s))
		(*s)++;
	return (*s);
}

bool	tokenize(t_input *input)
{
	char	*line;
	char	*start;
	char	*token;

	line = input->line_read;
	while (line && *line)
	{
		start = find_start(&line);
		if (*start == '\0')
			return (0);
		if (find_end(&line) == FAIL)
			return (1);
		token = ft_substr(start, 0, (line - start));
		add_token_to_list(&input->token_list, token);
	}
	return (0);
}
