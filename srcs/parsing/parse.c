/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:49 by user42            #+#    #+#             */
/*   Updated: 2022/08/16 09:00:04 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	parse(t_sh *sh, t_input *input)
{
	if (!*(input->line_read))
		return (1);
	if (tokenize(input))
		return (1);
 	if (!input->token_list)
		return (1);
	
	// print token list
	if (input->token_list)
	{
		t_list	*lst = input->token_list;
		while (lst)
		{
			printf("tok = [%s]\n", (char *)lst->content); //| type = %d\n", (char *)lst->content, lst->type);
			lst = lst->next;
		}
		ft_printerror("___________\n\n");
	}
	//end of print

	if (lexer(input->token_list))
		return (1);
	if (build_cmd_lst(sh, input->token_list))
		return (1);
	
	//print cmd_lst
	t_cmd	*tmp = sh->cmd_list;
	size_t	i = 0;
	while(tmp)
	{
		printf("cmd = ");
		i = 0;
		while (tmp->args && tmp->args[i])
		{
			printf("[%s]", tmp->args[i++]);
			printf(" ");
		}
		printf("\n");
		printf("\tredir_error = %d\n", tmp->redir_error);
		if (!tmp->redir_error)
		{
			printf("\tredir_in.filename = %s  | ", tmp->redir_in.filename);
			printf("redir_in.is_heredoc = %d | ", tmp->redir_in.is_heredoc);
			printf("redir_in.quoted_delim = %d\n", tmp->redir_in.quoted_delim);
			printf("\tredir_out.filename = %s | ", tmp->redir_out.filename);
			printf("redir_out.is_append = %d\n", tmp->redir_out.is_append);
			printf("\n");
		}
		tmp = tmp->next;
	}
	//end of print
	return (0);
}

/*



*/