/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:49:09 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/15 18:59:44 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_input *input, char *s)
{
	write(2, "minish: ", 8);
	write(2, s, ft_stlren(s));
	
	end(input);
}
