/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:41:07 by user42            #+#    #+#             */
/*   Updated: 2022/06/11 10:25:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_cmd_to_list(t_cmd **head, t_cmd *new)
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

static char	**cmd_tab(t_list *token)
{
	char *tmp;
	char	**cmd_tab;
	size_t	size;
	size_t	i;

	cmd_tab = NULL;
	size = get_cmd_tab_sz(token);
	printf("cmb_tab_size = %zu\n", size);
	cmd_tab = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (token && !is_separator(token->type))
	{
		if (token->type == WORD)
		{
			cmd_tab[i] = ft_strdup((char *)token->content);
			while (token->next && token->next->type == WORD)
			{
				token = token->next;
				tmp = cmd_tab[i];
				cmd_tab[i] = ft_strjoin(tmp, (char *)token->content);
				free(tmp);
//				ft_free_mode(ft_strjoin, &cmd_tab[i], (char *)token->content);
			}
		}
		token = token->next;
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

static t_cmd	*create_new_cmd(t_list *token)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->cmd_tab = cmd_tab(token);
	new->next = NULL;
	ft_tab_display(new->cmd_tab);
	cmd_redirections(new, token);
	return (new);
}

static void	token_to_cmd_lst(t_sh *sh, t_list *token)
{
	t_cmd	*new_cmd;
	t_cmd 	*head;

	head = sh->cmd_list;
	while (token)
	{
		new_cmd = NULL;
		new_cmd = create_new_cmd(token);
		add_cmd_to_list(&head, new_cmd);
		while (token && !is_separator(token->type))
			token = token->next;
		if (token && is_separator(token->type))
			token = token->next;
	}

//just to display
	t_cmd	*cmd;
	cmd = head;
	while (cmd)
	{
		ft_tab_display(cmd->cmd_tab);
		cmd = cmd->next;
	}
}

int	parser(t_input *input, t_sh *sh)
{
	set_types_to_expand(input->token_list);
	token_expand(input->token_list, sh->env);
	complete_types(input->token_list);
	ft_lstiter(input->token_list, display_token_list);

	sh->cmd_nb = get_cmd_nb(input->token_list);
	printf("cmd_nb = %zu\n", sh->cmd_nb);

	token_to_cmd_lst(sh, input->token_list);


//	cmd_redirections(input->token_list);
	return (1);
}