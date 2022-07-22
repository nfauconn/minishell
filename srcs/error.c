/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:49:09 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/23 01:02:23 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*perror_and_free(t_input *input, char *s)
{
	ft_printerror("minish: %s\n", s);
	clear_input(input);
	return (NULL);
}

int	lex_error(char *s)
{
	ft_printerror("minish: syntax error near unexpected token `%s'\n", s);
	return (FAILURE);
}

int	exec_error(char *s1, char *s2)
{
	if (s1 && s2)
		ft_printerror("minish: %s%s\n", s1, s2);
	else
		ft_printerror("please enter 2 valid strings in ft_printerror\n");
	return (FAILURE);
}

void	error_display(char *s1, char *s2, char *s3)
{
	if (s1 && !s2 && !s3)
		ft_printerror("minish: %s\n", s1);
	else
		ft_printerror("minish: %s: %s%s\n", s1, s2, s3);
}

void	error_exit(char *cmd_name, int8_t error_code)
{
	struct stat	mode;

	if (!*cmd_name)
		error_display("\'\'", "command not found", 0);
	else if (error_code == NOT_FOUND)
	{
		if (!is_relative_path(cmd_name))
		{
			if (stat(cmd_name, &mode) == 0 && S_ISDIR(mode.st_mode))
				error_display(cmd_name, "Is a directory", 0);
			else
				error_display(cmd_name, "No such file or directory", 0);
		}
		else
			error_display(cmd_name, "command not found", 0);
	}
	else if (error_code == NOT_EXECUTABLE)
		error_display(cmd_name, "permission denied", 0);
	exit(error_code);
}
