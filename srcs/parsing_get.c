/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:10:00 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/10 11:55:45 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	char	*line_read;

	line_read = readline("minish> ");
	if (line_read && *line_read)
	{
		if (ft_strncmp(line_read, "exit", 4) == 0)
		{
			free(line_read);
			exit(0);
		}
		add_history(line_read);
	}
	else if (line_read && *line_read == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (!line_read)
	{
		ft_putstr_fd("exit\n", 1);
		free(line_read);
		exit(0);
	}
	return (line_read);
}

size_t	get_cmd_tab_sz(t_list *token)
{
	size_t	count;

	count = 0;
	while (token && !is_separator(token->type))
	{
		if ((token->type == WORD || is_quote(token->type)) && !is_blank(token->type))
			count++;
		token = token->next;
	}
	return (count);
}

size_t	get_cmd_nb(t_list *token)
{
	size_t	cmd_nb;

	cmd_nb = 1;
	while (token)
	{
		if (is_separator(token->type))
			cmd_nb++;
		token = token->next;
	}
	return (cmd_nb);
}



/*void	set_types_to_expand(t_list *token)
{
	char	*tmp;

	while (token)
	{
		tmp = (char *)token->content;
		token->type = *tmp;
		if (token->type == IN_REDIR)
		{
			if (!ft_strcmp(tmp, "<<"))
			{
				token->type = HEREDOC;
				if (token->next)
					token->next->type = DELIMITER;
			}
			else if (token->next)
				token->next->type = INFILE_PATH;
		}
		else if (token->type == OUT_REDIR)
		{
			if (!ft_strcmp(tmp, ">>"))
			{
				token->type = APPEND_REDIR;
				if (token->next)
					token->next->type = APPEND_OUTFILE_PATH;
			}
			else if (token->next)
				token->next->type = TRUNC_OUTFILE_PATH;
		}
		else if (token->type == '$' && token->type != DELIMITER)
		{
			tmp++;
			if (*tmp == '\0')
				token->type = WORD;
			else
				token->type = TO_EXPAND;
		}
		else if (token->type != PIPE && !is_quote(token->type))
			token->type = WORD;
		token = token->next;
	}
}*/