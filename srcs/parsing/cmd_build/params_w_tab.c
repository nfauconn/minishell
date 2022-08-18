/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_w_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:20 by noe               #+#    #+#             */
/*   Updated: 2022/08/18 23:42:28 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	len_until_blank(char *s)
{
	size_t	i;
	char	quote;

	i = 0;
	while (s && s[i])
	{
		if (is_quote(s[i]))
		{
			quote = s[i++];
			while (s[i] != quote)
				i++;
			i++;
		}
		else if (is_blank(s[i]))
			return (i);
		else
			i++;
	}
	return (i);
}

static t_bool	fill_arg(t_sh *sh, t_cmd *cmd, size_t *index, char *token)
{
	size_t	len;
	char	*tmp;

	len = 0;
	while (*token)
	{
		cmd->args[*index] = NULL;
		len = len_until_blank(token);
		tmp = ft_substr(token, 0, len);
		cmd->args[*index] = expand(tmp, sh);
		free(tmp);
		tmp = cmd->args[*index];
		cmd->args[*index] = remove_quote(tmp);
		free(tmp);
		token += len;
		while (is_blank(*token))
			token++;
		(*index)++;
	}
	return (0);
}

t_bool	set_cmd_params(t_sh *sh, t_list *token, t_cmd *cmd)
{
	size_t	args_nb;
	size_t	arg_no;

	args_nb = get_args_nb(token);
	arg_no = 0;
	cmd->args = (char **)malloc(sizeof(char *) * (args_nb + 1));
	if (!cmd->args)
		return (1);
	while (token && token->type != '|')
	{
		if (is_redir(token->type))
		{
			if (!cmd->redir_error)
				set_redir(sh, cmd, (char *)token->content);
		}
		else
			fill_arg(sh, cmd, &arg_no, (char *)token->content);
		token = token->next;
	}
	cmd->args[args_nb] = NULL;
	return (0);
}