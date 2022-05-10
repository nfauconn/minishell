/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:54:56 by user42            #+#    #+#             */
/*   Updated: 2022/05/10 17:15:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	ft_is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
}

static int	is_ending_quote(char **s, char c)
{
	while (**s && **s != '|')
	{
		if (**s == c)
			return (1);
		(*s)++;
	}
	return (0);
}

static void	find_end_token(char **s)
{
	char	*tmp;
	char	c;

	c = **s;
	if (ft_is_quote(c))
	{
		(*s)++;
		tmp = (*s);
		if (is_ending_quote(s, c))
		{
			(*s)++;
			return ;
		}
		else
			(*s) = tmp;
	}
	while (ft_isprint(**s) && !ft_is_whitespace(**s) && (**s) != '\'' && (**s) != '\"')
		(*s)++;
}

static int	word_count(char *s)
{
	int		count;
	char	*tmp;

	count = 0;
	while (*s)
	{
		while (ft_is_whitespace(*s))
			s++;
		tmp = s;
		if (tmp)
			count++;
		find_end_token(&s);
	}
	return (count);
}

char	**tokenized_cmd(t_input *input, char *cmd)
{
	char	*tmp;
	char	**tokenized;
	int		size;
	int		i;

	(void)input;
	size = word_count(cmd);
	tokenized = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
  	while (i < size)
	{
		while (ft_is_whitespace(*cmd))
			cmd++;
		tmp = cmd;
		find_end_token(&cmd);
		if (ft_is_quote(*cmd))
			cmd++;
		tokenized[i] = ft_substr(tmp, 0, cmd - tmp);
		i++;
	}
	tokenized[size] = NULL;
	return (tokenized);
}
