/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:51 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/08 13:29:08 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(t_list *token)
{
	t_list	*curr;
	char	*tok;
	int		redir[2];

	curr = token;
	errno = 0;
	while (curr && !errno)
	{
		tok = (char *)curr->content;
		if (curr->type == IN_REDIR)
		{
			close(redir[0]);
			if (curr->next)
				redir[0] = open((char *)curr->next->content, O_RDONLY);
		}
		else if (token->type == OUT_REDIR)
		{
			close(redir[1]);
			if (curr->next)
				redir[1] = open((char *)curr->next->content,  O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		curr = curr->next;
	}
	if (errno)
	{
		ft_printerror("minish: %s: %s\n", (char *)curr->content, strerror(errno));
	}
}
