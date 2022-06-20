/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:49:09 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/20 17:34:51 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_and_free(t_input *input, char *s)
{
	ft_printerror("minish: %s\n", s);
	end_input(input);//, sh);
}

int	lex_error(char *s)
{
	ft_printerror("minish: syntax error near unexpected token `%s'\n", s);
	return (FAILURE);
}

int	exec_error(char *s1, char *s2)
{
	if (s1 && s2)
		ft_printerror("%s%s\n", s1, s2);
	else
		ft_printerror("please enter 2 valid strings in ft_printerror\n");
	return (FAILURE);
}

void	error_display(char *s1, char *s2)
{
	ft_printerror("%s: %s\n", s1, s2);
}

void	error_exit(char *cmd_name, int8_t error_code)
{
	if (error_code == NOT_FOUND)
		error_display(cmd_name, "command not found");
	else if (error_code == NOT_EXECUTABLE)
		error_display(cmd_name, "permission denied");
	exit(error_code);
}
