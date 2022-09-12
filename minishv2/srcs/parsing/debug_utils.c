/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:28:38 by noe               #+#    #+#             */
/*   Updated: 2022/09/10 18:09:08 by nfauconn         ###   ########.fr       */
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
	t_redir	*rin;
	t_redir	*rout;

	rin = tmp->redir_in;
	rout = tmp->redir_out;
	if (rin)
	{
		printf("\tredir_in.filename = %s  | ", rin->filename);
		printf("redir_in.is_heredoc = %d | ", rin->is_heredoc);
		printf("redir_in.quoted_delim = %d\n", rin->quoted_delim);
		printf("\n");
	}
	while (rout)
	{
		printf("\tredir_out.filename = %s | ", rout->filename);
		printf("redir_out.is_append = %d\n", rout->is_append);
		rout = rout->next;
	}
}

void	print_commands(t_sh *sh)
{
	t_cmd	*tmp;
	size_t	i;

	tmp = sh->cmd_list;
	i = 0;
	while (tmp)
	{
		printf("cmd->args = ");
		i = 0;
		while (tmp->args && tmp->args[i])
		{
			printf("[%s]", tmp->args[i++]);
			printf(" ");
		}
		printf("\n");
		printf("\tredir_error = %d\n", tmp->redir_error);
		if (!tmp->redir_error)
			print_redir(tmp);
		tmp = tmp->next;
	}
}
