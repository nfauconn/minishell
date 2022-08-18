/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:06 by user42            #+#    #+#             */
/*   Updated: 2022/08/18 17:10:54 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_last_status;

int	main(int ac, char **av, char **env)
{
	t_input			input;
	t_sh			sh;

	(void)ac;
	(void)av;
	g_last_status = 0;
	init_sh(&sh);
	sh.env = init_env(env);
	while (1)
	{
		signal_catching_mode(INTERACTIVE);
		init_input(&sh, &input);
		if (parse(&sh, &input) == OK)
		{
			clear_input(&input);
			launch(&sh);
		}
		reset_sh(&sh);
	}
}
