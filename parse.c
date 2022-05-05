/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:17:26 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/05 18:32:57 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	go_forward_whitespaces(char **line)
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
