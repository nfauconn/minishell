/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:20:58 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/08 14:49:02 by mdankou          ###   ########.fr       */
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

char	*build_prompt(t_list *env)
{
	char	*prompt;
	char	*cwd;

	prompt = ft_strdup(B_GREEN "🐱 MINISH 🐱:"B_MAGENTA);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = var_value("PWD", 3, env);
	if (!cwd)
		cwd = ft_strdup(".");
	ft_strfjoin(&prompt, cwd);
	free(cwd);
	ft_strfjoin(&prompt, NEUTRAL"$ ");
	return (prompt);
}
