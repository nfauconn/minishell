/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:06 by user42            #+#    #+#             */
/*   Updated: 2022/07/31 18:42:25 by nfauconn         ###   ########.fr       */
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
		if (parsing(&sh, &input) == SUCCESS)
		{
			clear_input(&input);
			launch(&sh);
		}
		reset_sh(&sh);
	}
}
