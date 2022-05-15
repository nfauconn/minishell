/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:55:15 by user42            #+#    #+#             */
/*   Updated: 2022/05/15 14:47:54 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** SIGINT = CTRL-C
** write '\n' moves to a new line (if not : prompt displayed on the same line as ^C)
** rl_on_new_line() regenerates the prompt on a newline
** rl_replace_line() clears the previous text if ctrl-C pressed in a non-empty line
** rl_redisplay() displays the new prompt
*/

static void	new_line(int sig_num, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	set_sigact(int signum, struct sigaction *s)
{
	s->sa_flags = SA_SIGINFO;
	sigemptyset(&s->sa_mask);
	sigaction(signum, s, NULL);
}

void	signal_catching_mode(int mode)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_backslash;

	if (mode == INTERACTIVE)
	{
		ctrl_c.sa_handler = NULL;
		ctrl_c.sa_sigaction = new_line;
		set_sigact(SIGINT, &ctrl_c);
		ctrl_backslash.sa_handler = SIG_IGN;
	}
	else if (mode == PGM_EXEC)
	{
		ctrl_c.sa_handler = SIG_DFL;
	}
}
