/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:06 by user42            #+#    #+#             */
/*   Updated: 2022/05/18 12:27:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_input(void)
{
	char	*line_read;

	line_read = readline("minishell> ");
	if (line_read && *line_read)
	{
		if (ft_strncmp(line_read, "exit", 4) == 0)
		{
			free(line_read);
			exit(1);
		}
		add_history(line_read);
	}
	else if (line_read && *line_read == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		free(line_read);
		exit(1);
	}
	return (line_read);
}

int	main(void)
{
	t_input	input;

	while (1)
	{
		signal_catching_mode(INTERACTIVE);
		init(&input);
		input.line_read = get_input();
		tokenizer(&input, input.line_read);
		lexer(&input, input.token_list);
		end(&input);
	}
}
