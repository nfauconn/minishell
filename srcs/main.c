/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:06 by user42            #+#    #+#             */
/*   Updated: 2022/08/20 14:46:55 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern uint8_t	g_last_status;

int	main(int ac, char **av, char **env)
{
	t_input			input;
	t_sh			sh;

	(void)ac;
	(void)av;
	g_last_status = 0;
	init_sh(&sh);
	sh.env = init_env(env);
	if (!sh.env)
		return (sh_perror("malloc failure"));
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
