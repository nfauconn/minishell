/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:10:00 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/31 17:34:53 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define MINISH_COLOR "\e[1;35m"
#define DIRS_COLOR "\e[0;36m"
#define INPUT_COLOR "\e[0m"

#include "minishell.h"

static void	readprompt(char **line_read)
{
	char	*prompt;
	char	*cwd;

	prompt = ft_strdup(MINISH_COLOR"🐱 MINISH 🐱: "DIRS_COLOR);
	cwd = getcwd(NULL, 0);
	ft_strfjoin(&prompt, cwd);
	free(cwd);
	ft_strfjoin(&prompt, "> "INPUT_COLOR);
	*line_read = readline(prompt);
	free(prompt);
}

char	*get_input(t_sh *sh)
{
	char	*line_read;

	readprompt(&line_read);
	if (!line_read)
		exit_clear_minish(sh, 0);
	if (line_read && *line_read == '\0')
		redisplay_prompt();
	if (line_read && *line_read)
		add_history(line_read);
	sh->line_nb++;
	return (line_read);
}

int	init_input(t_sh *sh, t_input *input)
{
	input->line_read = get_input(sh);
	input->token_list = NULL;
	return (0);
}
