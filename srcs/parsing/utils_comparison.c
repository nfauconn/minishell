/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_comparison.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:55:34 by user42            #+#    #+#             */
/*   Updated: 2022/07/23 00:55:01 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_sep(int c)
{
	return (c == PIPE);
}

int	is_outfilename(int c)
{
	return (c == OUTFILE_NAME || c == APPEND_OUTFILE_NAME);
}

int	is_rediroperator(int c)
{
	return (c == '<' || c == '>');
}

int	is_filename(int c)
{
	return (c == INFILE_NAME || c == HEREDOC_DELIM
		|| c == OUTFILE_NAME || c == APPEND_OUTFILE_NAME);
}

int	is_relative_path(char *filename)
{
	if (ft_strchr(filename, '/'))
		return (0);
	return (1);
}
