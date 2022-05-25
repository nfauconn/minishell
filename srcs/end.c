/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:09:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/25 16:40:03 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end(t_input *input)
{
	if (input->line_read)
		ft_strdel(&input->line_read);
	if (input->token_list)
		ft_lstclear(&input->token_list, free);
	input = NULL;
}
