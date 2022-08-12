/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:57:56 by user42            #+#    #+#             */
/*   Updated: 2022/08/06 21:43:45 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	go_through_same_char(char **s)
{
	int	c;

	c = **s;
	(*s)++;
	while (**s && **s == c)
	{
		(*s)++;
		if (**s != c)
			return (0);
	}
	return (0);
}

t_bool	tokenize_redir(char **s)
{
	while (is_operator(**s))
		(*s)++;
	while (is_blank(**s))
		(*s)++;
	while (is_operator(**s))
		(*s)++;
	while (**s && !is_metachar(**s))
	{
		if (is_quote(**s) && check_closing_quote(s, **s) == FAIL)
			return (1);
		(*s)++;
	}
	return (0);
}

t_bool	check_closing_quote(char **s, char quote)
{
	while (**s)
		if (*(++(*s)) == quote)
			return (0);
	return (sh_perror("does not handle non closed quotes"));
}

void	skip_token(t_list **token, int to_skip)
{
	if (token && *token)
		*token = (*token)->next;
	if (token && *token && *(char *)(*token)->content == to_skip)
		*token = (*token)->next;
}

void	add_token_to_list(t_list **token_list, char *token)
{
	t_list	*new;

	new = ft_lstnew(token);
	new->type = *token;
	ft_lstadd_back(token_list, new);
}
