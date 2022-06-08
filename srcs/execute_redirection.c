/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:51 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/08 16:17:35 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(t_list *token)
{
	char	*tok;
	int		redir[2];

	errno = 0;
	while (token && !errno)
	{
		tok = (char *)token->content;
		if (token->type == IN_REDIR)
		{
			close(redir[0]);
			if (token->next)
				redir[0] = open((char *)token->next->content, O_RDONLY);
		}
		else if (token->type == OUT_REDIR)
		{
			close(redir[1]);
			if (token->next)
				redir[0] = open("/tmp/.here_doc",  O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		else if (token->type == HEREDOC)
		{
			redir[0] = open((char *)token->next->content, O_RDWR);
		}
		token = token->next;
	}
	if (errno)
	{
		ft_printerror("minish: %s: %s\n", (char *)token->content, strerror(errno));
	}
}
