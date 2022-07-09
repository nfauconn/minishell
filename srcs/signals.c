/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:55:15 by user42            #+#    #+#             */
/*   Updated: 2022/07/09 19:29:37 by nfauconn         ###   ########.fr       */
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
	//if (sig_num == SIGQUIT)
	ft_printerror("Quit (core dumped)\n");
	exit(sig_num + 128);
}

static void	new_line(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_printerror("coucou je fais nimporte quoi\n");
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_catching_mode(int mode)
{
	ft_printerror("mode = %d\n", mode);
	if (mode == INTERACTIVE)
	{
		ft_printerror("mode interactive_process\n");

		signal(SIGINT, new_line);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SH_PROCESS)
	{
		ft_printerror("mode sh_process\n");
		signal(SIGINT, SIG_DFL);
	}
	else if (mode == CHILD_PROCESS)
	{
		ft_printerror("mode child_process\n");
		signal(SIGINT, exit_yourself);
		signal(SIGQUIT, exit_yourself);
	}
}
