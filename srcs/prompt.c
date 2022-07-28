/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:20:58 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/28 09:27:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** READLINE FUNCTIONS
** rl_on_new_line() regenerates the prompt on a newline
** rl_replace_line() clears the already written text on prev line
** rl_redisplay() displays the new prompt
*/

void	redisplay_prompt(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
