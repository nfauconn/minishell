/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:04:06 by user42            #+#    #+#             */
/*   Updated: 2022/07/28 08:33:03 by user42           ###   ########.fr       */
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
	init_sh(&sh, env);
	while (1)
	{
		signal_catching_mode(INTERACTIVE);
		init_input(&sh, &input);
		if (parsing(&sh, &input) == SUCCESS)
			launch(&sh);
		reset_for_new_input(&sh, &input);
	}
}
