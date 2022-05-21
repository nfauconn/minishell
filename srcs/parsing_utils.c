/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:57:56 by user42            #+#    #+#             */
/*   Updated: 2022/05/18 18:30:01 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_meta(int c)
{
	return (c == PIPE || c == IN_REDIR || c == OUT_REDIR);
}

int	is_quote(int c)
{
	return (c == QUOTE || c == DOUBLE_QUOTE);
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
