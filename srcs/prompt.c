/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:20:58 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/01 16:31:44 by user42           ###   ########.fr       */
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

	prompt = ft_strdup(MINISH_COLOR"🐱 MINISH 🐱: "DIRS_COLOR);
	cwd = getcwd(NULL, 0);
	ft_strfjoin(&prompt, cwd);
	free(cwd);
	ft_strfjoin(&prompt, "> "INPUT_COLOR);
	return (prompt);
}
