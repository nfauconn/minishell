/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:49:09 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 22:32:57 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	sh_perror(char *s)
{
	ft_printerror("minish: %s\n", s);
	return (1);	
}

bool	lex_perror(char *s)
{
	ft_printerror("minish: syntax error near unexpected token `%s'\n", s);
	return (1);
}

bool	error_display(char *s1, char *s2, char *s3)
{
	ft_printerror("minish: %s: %s%s\n", s1, s2, s3);
	return (1);
}

void	perror_exit(t_sh *sh, char *s1, char *s2, unsigned char exit_code)
{
	error_display(s1, s2, 0);
	exit_clear_child(sh, exit_code);
}
