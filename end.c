/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:09:54 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/11 19:21:20 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end(t_input *input)
{
	if (input->line_read)
		free(input->line_read);
	if (input->token_line)
		ft_lstclear(&input->token_line, free);
}
