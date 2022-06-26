/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_comparison.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:55:34 by user42            #+#    #+#             */
/*   Updated: 2022/06/26 23:01:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(int c)
{
	return (c == PIPE);
}

int	is_infile(int c)
{
	return (c == INFILE_PATH || c == DELIMITER);
}

int	is_outfile(int c)
{
	return (c == TRUNC_OUTFILE_PATH || c == APPEND_OUTFILE_PATH);
}

int	is_redir(int c)
{
	return (c == IN_REDIR || c == OUT_REDIR || c == HEREDOC
		|| c == APPEND_REDIR);
}

int	is_redir_path(int c)
{
	return (c == INFILE_PATH || c == DELIMITER
		|| c == TRUNC_OUTFILE_PATH || c == APPEND_OUTFILE_PATH);
}
