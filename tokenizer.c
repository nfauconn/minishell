/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/15 19:32:47 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
}

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

	if (ft_is_quote(**s) && (*((*s) + 1) != '\0'))
	{
		tmp = (*s)++;
		*s = find_closing_quote(s, *tmp);
		if (*s)
			return (*s);
		else
			*s = tmp;
	}
	if (**s == IN_REDIR || **s == OUT_REDIR || **s == PIPE)
	{
		found_c = **s;
		while (**s == found_c)
			(*s)++;
		return (*s);
	}
	while (**s && !ft_iswhitespace(**s) && **s != PIPE)
	{
		(*s)++;
		if (ft_is_quote(**s) || **s == IN_REDIR || **s == OUT_REDIR)
			return (*s) ;
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
	printf("token : (%s)\n", (char *)content);
}

static void	add_token_to_list(t_list **token_list, char *token)
{
	t_list	*new;

	new = ft_lstnew(token);
	ft_lstadd_back(token_list, new);
}

void	tokenize_input(t_input *input, char *line)
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
		}
		add_token_to_list(&input->token_list, token);
		if (ft_iswhitespace(*line))
		{
			token = ft_strdup(" ");
			add_token_to_list(&input->token_list, token);
		}
		start = NULL;
		end = NULL;
	}
	ft_lstiter(input->token_list, display_list);
}
