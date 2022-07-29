/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:49:09 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/30 01:25:47 by user42           ###   ########.fr       */
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

int	exec_perror(char *s1, char *s2)
{
	if (s1 && s2)
		ft_printerror("minish: %s: %s\n", s1, s2);
	return (FAILURE);
}

void	error_display(char *s1, char *s2, char *s3)
{
	if (s1 && !s2 && !s3)
		ft_printerror("minish: %s\n", s1);
	else
		ft_printerror("minish: %s: %s%s\n", s1, s2, s3);
}
