/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:57:56 by user42            #+#    #+#             */
/*   Updated: 2022/06/21 18:22:39 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

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
	return(c == INFILE_PATH || c == DELIMITER 
		|| c == TRUNC_OUTFILE_PATH || c == APPEND_OUTFILE_PATH);
}

int	is_quote(int c)
{
	return (c == QUOTE || c == DB_QUOTE);
}

int	is_word(int c)
{
	return (!is_quote(c) && !is_redir(c) && !is_blank(c) && !is_sep(c));
}

t_list *skip_token(t_list *token, int to_skip)
{
	token = token->next;
	if (token && token->type == to_skip)
		token = token->next;
	return (token);
}

void	display_token_list(t_list *lst)
{
	while (lst)
	{
		printf("tok = %20s | type = %d\n", (char *)lst->content, lst->type);
		lst = lst->next;
	}
}

void	add_token_to_list(t_list **token_list, char *token)
{
	t_list	*new;

	new = ft_lstnew(token);
	ft_lstadd_back(token_list, new);
}
