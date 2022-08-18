/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:28:38 by noe               #+#    #+#             */
/*   Updated: 2022/08/18 17:10:18 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	print_token_list(t_input *input)
{
	t_list	*lst;

	lst = input->token_list;
	while (lst)
	{
		printf("tok = [%s]\n", (char *)lst->content);
		lst = lst->next;
	}
	printf("___________\n\n");
}

static void	print_redir(t_cmd *tmp)
{
	printf("\tredir_in.filename = %s  | ", tmp->redir_in.filename);
	printf("redir_in.is_heredoc = %d | ", tmp->redir_in.is_heredoc);
	printf("redir_in.quoted_delim = %d\n", tmp->redir_in.quoted_delim);
	printf("\tredir_out.filename = %s | ", tmp->redir_out.filename);
	printf("redir_out.is_append = %d\n", tmp->redir_out.is_append);
	printf("\n");
}

void	print_arg_lst(t_list *arg_lst)
{
	printf("cmd->args_lst = ");
	while (arg_lst)
	{
		printf("[%s] ", (char *)arg_lst->content);
		arg_lst = arg_lst->next;
	}
	printf("\n");
}

void	print_commands(t_sh *sh)
{
	t_cmd	*tmp;
	size_t	i;

	tmp = sh->cmd_list;
	i = 0;
	while (tmp)
	{
		print_arg_lst(tmp->args_lst);
		printf("cmd->args_tab = ");
		i = 0;
		while (tmp->args_tab && tmp->args_tab[i])
		{
			printf("[%s]", tmp->args_tab[i++]);
			printf(" ");
		}
		printf("\n");
		printf("\tredir_error = %d\n", tmp->redir_error);
		if (!tmp->redir_error)
			print_redir(tmp);
		tmp = tmp->next;
	}
}
