/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:59:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/11 18:07:48 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	one_token()
{
	char	*token;
	t_list	*new;

	token = ft_substr(jefheri);
	new = lst_new(token);
	ft_lst_add_back(input->token_line, new);
}

void	tokenize_input(t_input *input, char *line)
{
	
	while (*line)
	{
		while (line = whitespace)
			line++;
		if (line)
		{
			- QUOTE
			- caracteres --> avancer jusqua - whitespace ou /0 ou '|'= END OF TOKEN
											- quote -->

											
		}
		
	}
}
