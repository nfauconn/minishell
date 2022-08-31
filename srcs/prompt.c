/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:20:58 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/31 19:07:01 by nfauconn         ###   ########.fr       */
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

char	*build_prompt(void)
{
	char	*prompt;
	char	*cwd;

	prompt = ft_strdup(B_GREEN "🐱 MINISH 🐱:"B_MAGENTA);
	cwd = getcwd(NULL, 0);
	ft_strfjoin(&prompt, cwd);
	free(cwd);
	ft_strfjoin(&prompt, NEUTRAL"$ ");
	return (prompt);
}
