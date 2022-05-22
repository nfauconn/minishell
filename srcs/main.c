/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:06 by user42            #+#    #+#             */
/*   Updated: 2022/05/22 17:54:24 by nfauconn         ###   ########.fr       */
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
	else
	{
		ft_putstr_fd("exit\n", 1);
		free(line_read);
		exit(0);
	}
	return (line_read);
}

int	main(void)
{
	t_input	input;
	t_sh	sh;

	while (1)
	{
		signal_catching_mode(INTERACTIVE);
		init_input(&input);
		input.line_read = get_input();
		tokenizer(&input, input.line_read);
		if (lexer(input.token_list) == SUCCESS)
		{
			init_sh(&sh);
		}		
		end(&input);
	}
}
