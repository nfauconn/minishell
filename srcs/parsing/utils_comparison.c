/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_comparison.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:55:34 by user42            #+#    #+#             */
/*   Updated: 2022/07/12 21:05:53 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_sep(int c)
{
	return (c == PIPE);
}

int	is_infile(int c)
{
	return (c == INFILE || c == DELIMITER);
}

int	is_outfile(int c)
{
	return (c == TRUNC || c == APPEND_FILE);
}

int	is_redir(int c)
{
	return (c == '<' || c == '>' || c == HEREDOC
		|| c == APPEND);
}

int	is_redir_path(int c)
{
	return (c == INFILE || c == DELIMITER
		|| c == TRUNC || c == APPEND_FILE);
}
