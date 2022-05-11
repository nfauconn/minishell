/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:09:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/11 17:20:25 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_list(t_list *list)
{
	t_list	*tmp;
	t_list	*to_free;

	while (tmp->next != NULL)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	free(tmp);
}

void	end(t_input *input)
{
	if (input->line_read)
		free(input->line_read);
	if (input->token_line)
		free_list(input->token_line);
}
