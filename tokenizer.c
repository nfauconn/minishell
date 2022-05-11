/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/11 20:00:27 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
}

static void	find_end(char **s)
{
	while (**s && (**s != '|') && !ft_is_whitespace(**s))
	{
		if (ft_is_quote(**s))
		{
			/*  tmp = *s (to keep the address in case no closing quote : restart the exploring)
				go forward *s while **s != '|' to find the same quote /!\ if quote then no whitespace then quote : still go forward
				> if found same quote -> return ; (because end of token is found)
				> if didnt -> *s = tmp ; (*s)++; continue to search a whitespace to end token
			*/
		}
		(*s)++;
	}
}

static void	find_start(char **s)
{
	while (ft_is_whitespace(**s))
		(*s)++;
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

	while (*line)
	{
		find_start(&line);
		if (*line == '\0')
			break ;
		start = line;
		find_end(&line);
		end = line;
		token = ft_substr(start, 0, end - start);
		if (token)
		{
			new = ft_lstnew(token);
			ft_lstadd_back(&input->token_line, new);
		}
	}
	ft_lstiter(input->token_line, display_list);
	printf("\n");
}
