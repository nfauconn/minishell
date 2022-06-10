/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:06 by user42            #+#    #+#             */
/*   Updated: 2022/06/10 13:25:23 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	main(int ac, char **av, char **env)
{
	t_input	input;
	t_sh	sh;

	(void)ac; // if (ac == 3 && av[1] == "env -i") // if (ac == 3 && av[2] == "> /dev/random")
	(void)av;
	init_sh(&sh, env);
	while (1)
	{
		signal_catching_mode(INTERACTIVE);
		init_input(&input);
		if (tokenizer(&input, input.line_read) && lexer(input.token_list) && parser(&input, &sh))
		{
			//exec_cmd;
		}
		end(&input, &sh);
	}
	ft_lstclear(&sh.env, free);
}
