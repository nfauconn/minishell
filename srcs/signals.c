/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:55:15 by user42            #+#    #+#             */
/*   Updated: 2022/07/29 20:43:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"

unsigned char	g_last_status;

static void	new_line(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		redisplay_prompt();
		g_last_status = sig_num + 128;
	}
}

void	signal_catching_mode(int mode)
{
	if (mode == INTERACTIVE)
	{
		signal(SIGINT, new_line);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == PARENT_PROCESS)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
