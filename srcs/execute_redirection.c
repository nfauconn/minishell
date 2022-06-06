/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:51 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/06 17:12:07 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include "libft.h"

void	apply_redirections(t_list **token_list, int redir[2])
{
	t_list	*curr;

	curr = *token_list;
	errno = 0;
	while (curr && !errno)
	{
		if (*(char *)curr->content == '<')
		{
			close(redir[0]);
			redir[0] = open((char *)curr->next->content, O_RDONLY);
		}
		else if (*(char *)curr->content == '>')
		{
			close(redir[1]);
			redir[1] = open((char *)curr->next->content,  O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		curr = curr->next;
	}
	if (errno)
	{
		ft_printerror("minish: %s: %s\n", (char *)curr->content, strerror(errno));
	}
}