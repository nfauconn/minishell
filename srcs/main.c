/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:06 by user42            #+#    #+#             */
/*   Updated: 2022/06/27 15:44:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	main(int ac, char **av, char **env)
{
	t_input	input;
	t_sh	sh;

	(void)ac;
	(void)av;
	init_sh(&sh, env);
	while (1)
	{
		signal_catching_mode(INTERACTIVE);
		init_input(&sh, &input);
		if (parsing(&input, &sh) == SUCCESS)
			cmd_execute(&sh);
		end(&input, &sh);
	}
}
