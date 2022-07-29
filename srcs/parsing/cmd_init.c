/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:52:27 by user42            #+#    #+#             */
/*   Updated: 2022/07/29 23:08:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->index = 0;
	new->name = NULL;
	new->built_i = -1;
	new->args = NULL;
	new->env = NULL;
	new->env_paths = NULL;
	new->path = NULL;
	new->redir_in = NO_REDIR;
	new->redir_out = NO_REDIR;
	new->redir_out_type = 0;
	new->infile_name = NULL;
	new->heredoc_infile = 0;
	new->delim_quote = 0;
	new->outfile_name = NULL;
	new->access_error = 0;
	new->next = NULL;
	return (new);
}
