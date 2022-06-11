/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:57:56 by user42            #+#    #+#             */
/*   Updated: 2022/06/11 11:34:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_separator(int c)
{
	return (c == PIPE);
}

int	is_in_redir_path(int c)
{
	return (c == INFILE_PATH || c == DELIMITER);
}

int	is_out_redir_path(int c)
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
	return(c == INFILE_PATH || c == DELIMITER 
		|| c == TRUNC_OUTFILE_PATH || c == APPEND_OUTFILE_PATH);
}

int	is_quote(int c)
{
	return (c == QUOTE || c == DB_QUOTE);
}

void	display_token_list(void *content)
{
	printf("token : (%s)\n", (char *)content);
}

void	add_token_to_list(t_list **token_list, char *token)
{
	t_list	*new;

	new = ft_lstnew(token);
	ft_lstadd_back(token_list, new);
}
