/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:41:07 by user42            #+#    #+#             */
/*   Updated: 2022/06/10 13:28:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_list	*cmd_tab(t_cmd **head, t_list *token)
{
	char	**cmd_tab;
	size_t	size;
	size_t	i;

	cmd_tab = NULL;
	size = get_cmd_tab_sz(token);
	cmd_tab = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (token && !is_separator(token->type))
	{
		if (!is_redir(token->type) && !is_redir_path(token->type))
		{
			cmd_tab[i++] = (char *)token->content;
		}
		else
			apply_redirections(token, cmd)
		token = token->next;
	}
	cmd_tab[i] = NULL;
}

t_cmd	*create_new_cmd(t_list *token)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->tab = cmd_tab
	printf("cmb_tab_size = %zu\n", size);
}

static t_cmd	*token_to_cmd_lst(t_sh *sh, t_list *token)
{
	t_cmd	*new_cmd;

	while (token)
	{
		new_cmd = create_new_cmd(token);
		add_cmd_to_list(&sh->cmd_list, new_cmd);
		while (token && !is_separator(token->type))
			token = token->next;
	}
}

int	parser(t_input *input, t_sh *sh)
{
	set_types_to_expand(input->token_list);
	token_expand(input->token_list, sh->env);
	complete_types(input->token_list);

	sh->cmd_nb = get_cmd_nb(input->token_list);
	printf("cmd_nb = %zu\n", sh->cmd_nb);

	token_to_cmd_lst(sh, input->token_list);
//	apply_redirections(input->token_list);
	ft_lstiter(input->token_list, display_token_list);
	return (1);
}