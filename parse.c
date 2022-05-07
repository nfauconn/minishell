/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:17:26 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/07 17:41:21 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:17:14 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/07 17:09:53 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	go_through_print_whithout_ws(char **s)
{
	while (ft_isprint(**s) && !ft_is_whitespace(**s))
		(*s)++;
}

static void	go_through_whitespaces(char **s)
{
	while (ft_is_whitespace(**s))
		(*s)++;
}

static int	word_count(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		count++;
		go_through_whitespaces(&s);
		go_through_print_whithout_ws(&s);
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
		go_through_whitespaces(&cmd);
		tmp = cmd;
		go_through_print_whithout_ws(&cmd);
		tokenized[i] = ft_substr(tmp, 0, cmd - tmp);
		i++;
	}
	tokenized[size] = NULL;
	return (tokenized);
}


/* static void	go_forward_whitespaces(char **line)
{
	while (**line == 32 || (**line >= 9 && **line <= 13))
		(*line)++;
}

void	parse_line(t_input *input, char *line)
{
	char *tmp;

	go_forward_whitespaces(&line);
	if (*line == '<')
	{
		line++;
		input->is_stdin_redir = 1;
		go_forward_whitespaces(&line);
		tmp = line;
		while (ft_isprint(*line))
			line++;
		if ((*tmp == QUOTE && *(line - 1) == QUOTE)
			|| (*tmp == DOUBLE_QUOTE && *(line - 1) == DOUBLE_QUOTE))
			input->stdin_file = ft_substr(tmp, 1, line - 1 - tmp - 1);
		else
			input->stdin_file = ft_substr(tmp, 0, line - tmp);
	}
	go_forward_whitespaces(&line);
}
 */