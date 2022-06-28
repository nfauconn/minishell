/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:55:15 by user42            #+#    #+#             */
/*   Updated: 2022/06/28 13:30:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** SIGINT = CTRL-C
** write '\n' moves to a new line (if not : prompt displayed on the 
**															same line as ^C)
** rl_on_new_line() regenerates the prompt on a newline
** rl_replace_line() clears the previous text if ctrl-C pressed in a 
**																non-empty line
** rl_redisplay() displays the new prompt
*/

static void	exit_yourself(int sig_num)
{
	if (sig_num == SIGINT)
	{

		exit(130);
	}
}

static void	new_line(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_catching_mode(int mode)
{
	if (mode == INTERACTIVE)
	{
		signal(SIGINT, new_line);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == PGM_EXEC)
	{
		signal(SIGINT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, exit_yourself);
	}
}
