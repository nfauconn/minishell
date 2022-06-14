/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:49:09 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/14 16:36:13 by nfauconn         ###   ########.fr       */
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
	ft_printerror("minish: %s%s\n", s1, s2);
	return (FAILURE);
}