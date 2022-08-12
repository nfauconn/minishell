/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:49 by user42            #+#    #+#             */
/*   Updated: 2022/08/12 19:48:37 by nfauconn         ###   ########.fr       */
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
		ft_printerror("TOKEN_LIST :\n");
		t_list	*lst = input->token_list;
		while (lst)
		{
			printf("tok = [%s] | type = %d\n", (char *)lst->content, lst->type);
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
	ft_printf("CMD_LST :\n");
	t_cmd	*tmp = sh->cmd_list;
	size_t	i = 0;
	while(tmp)
	{
		printf("cmd = ");
		i = 0;
		while (tmp->args && tmp->args[i])
		{
			printf("%s", tmp->args[i++]);
			printf(" ");
		}
		printf("\n");
		printf("cmd->redir_in.filename = %s | ", tmp->redir_in.filename);
		printf("cmd->redir_in.is_heredoc = %d\n", tmp->redir_in.is_heredoc);
		printf("\n");
		tmp = tmp->next;
	}
	//end of print
	return (0);
}

/*



*/