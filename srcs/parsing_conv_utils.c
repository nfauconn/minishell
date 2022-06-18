/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_conv_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:37:25 by user42            #+#    #+#             */
/*   Updated: 2022/06/18 16:59:29 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_cmd_tab_sz(t_list *token)
{
	size_t	count;

	count = 0;
	while (token && !is_separator(token->type))
	{
		if ((token->type == WORD || is_quote(token->type)) && !is_blank(token->type))
			count++;
		token = token->next;
	}
	return (count);
}

size_t	get_cmd_nb(t_list *token)
{
	size_t	cmd_nb;

	cmd_nb = 1;
	while (token)
	{
		if (is_separator(token->type))
			cmd_nb++;
		token = token->next;
	}
	return (cmd_nb);
}

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

static char	**cmd_tab(t_list *token)
{
	char *tmp;
	char	**cmd_tab;
	size_t	size;
	size_t	i;

	cmd_tab = NULL;
	size = get_cmd_tab_sz(token);
	#ifdef DEBUG
	printf("cmb_tab_size = %zu\n", size);
	#endif
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
			#ifdef DEBUG
			printf("cmd_tab[%zu] = %s\n", i, cmd_tab[i]);
			#endif
			i++;
		}
		token = token->next;
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

t_cmd	*create_new_cmd(t_list *token)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->cmd_tab = cmd_tab(token);
	new->next = NULL;
	cmd_redirections(new, token);
	return (new);
}
