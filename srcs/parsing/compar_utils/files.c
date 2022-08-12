/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:56:44 by user42            #+#    #+#             */
/*   Updated: 2022/08/06 21:43:45 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	is_infilename(int c)
{
	return (c == INFILE_NAME);
}

t_bool	is_heredoc_delim(int c)
{
	return (c == HEREDOC_DELIM || c == QUOTED_HEREDOC_DELIM);
}

t_bool	is_outfilename(int c)
{
	return (c == OUTFILE_NAME || c == APPEND_OUTFILE_NAME);
}

t_bool	is_filename(int c)
{
	return (c == INFILE_NAME || c == HEREDOC_DELIM
		|| c == OUTFILE_NAME || c == APPEND_OUTFILE_NAME);
}

t_bool	is_absolute_path(char *filename)
{
	if (ft_strchr(filename, '/'))
		return (1);
	return (0);
}
