/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:54:56 by user42            #+#    #+#             */
/*   Updated: 2022/05/13 11:47:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	ft_is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
}

static int	is_ending_quote(char **s, char c)
{
	char	*tmp;

	while (**s && **s != '|')
	{
		if (**s == c)
		{
			tmp = *s;
			while (**s && ft_isprint(**s) && !ft_iswhitespace(**s) && **s != c && **s != '|')
			{
				(*s)++;
				if (ft_is_quote(**s))
				{
					(*s)++;
					break;
				}
				else if (!(**s))
				{
					(*s) = tmp;
					return (1);
				}
			}
		}
		else
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
	while (**s && ft_isprint(**s) && !ft_iswhitespace(**s) && !ft_is_quote(**s))
		(*s)++;
}

static void	find_end_token()
{
	end_of_token = cmd;
	find_end_token(&end_of_token);
	if (ft_is_quote(*end_of_token))
		end_of_token++;
}

static int	word_count(char *s)
{
	int		count;
	char	*tmp;

	count = 0;
	while (*s)
	{
		while (ft_iswhitespace(*s))
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
	char	*start;
	char	*end_of_token;
	char	**tokenized;
	int		size;
	int		i;

	(void)input;
	size = word_count(cmd);
	tokenized = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
  	while (i < size)
	{
		while (ft_iswhitespace(*cmd))
			cmd++;
		start = cmd;
		end_of_token = find_end_token(&cmd);
		tokenized[i] = ft_substr(end_of_token, 0, end_of_token - start);
		i++;
	}
	tokenized[size] = NULL;
	return (tokenized);
}
