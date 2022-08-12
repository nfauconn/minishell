/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:37:25 by user42            #+#    #+#             */
/*   Updated: 2022/08/12 21:26:55 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	add_cmd_to_list(t_cmd **head, t_cmd *new)
{
	t_cmd	*curr;

	if (!*head)
	{
		*head = new;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

t_cmd	*build_cmd(t_sh *sh, t_list *token, size_t i)
{
	(void)sh;
	t_cmd	*cmd;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	if (get_args_and_redir(sh, token, cmd))
		return (NULL);
	else
		cmd->name = cmd->args[0];
	cmd->built_i = is_builtin(cmd->name);
	cmd->index = i;
	return (cmd);
}

t_bool	build_cmd_lst(t_sh *sh, t_list *token)
{
	size_t	i;
	t_cmd	*new_cmd;

	i = 0;
	while (token)
	{
		new_cmd = build_cmd(sh, token, i);
		if (!new_cmd)
			return (1);
		add_cmd_to_list(&sh->cmd_list, new_cmd);
		i++;
		while (token && !is_sep_operator(token->type))
			token = token->next;
		if (token && is_sep_operator(token->type))
			token = token->next;
	}
	sh->cmd_nb = i + 1;
	return (0);
}

/* 
static void	fill_cmd_args(t_sh *sh, t_list *token, t_cmd *cmd)
{
	char	**to_add;
	size_t	size;

	size = get_cmd_tab_sz(token);
	printf("size = %zu\n", size);
	cmd->args = NULL;
	while (token && !is_sep_operator(token->type))
	{
		// /!\ quotes direct genre "cat -e"
		printf("token->content = %s\n | token->type = %c\n", (char *)token->content, (char)token->type);
		if (!is_rediroperator(token->type))
		{
			if (!cmd->args)
			{
				cmd->args = expand_split(sh, (char *)token->content, cmd);//faire un home maid split qui quote remove
				if (!cmd->args)
					return (NULL);
			}
			else
			{
				to_add = expand_split(sh, (char *)token->content, cmd);//home maid split
				cmd->args = ft_strarrayfreejoin(&cmd->args, &to_add);
				if (!cmd->args)
					return (NULL);
			}
		}
		token = token->next;
	}
	return (cmd->args);
}
 */

