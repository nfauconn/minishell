/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:20 by noe               #+#    #+#             */
/*   Updated: 2022/08/18 14:11:52 by noe              ###   ########.fr       */
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
	t_bool	to_field_split;

	len = 0;
	while (*token)
	{
		to_field_split = 0;
		cmd->args[*index] = NULL;
		len = len_until_blank(token);
		tmp = ft_substr(token, 0, len);
		cmd->args[*index] = expand(tmp, sh);
		if (!contains_quotes(tmp) && contains_quotes(cmd->args[*index]))
			to_field_split = 1;
		/*
		-> reallouer cmd->args en ajoutant le nombre de words contenus 
		-> split cmd->args[*index]
		-> ajouter chaque string a cmd->args a partir de index
		-> free le split
		*/
		free(tmp);
		if (ft_strchr(cmd->args[*index], '\'')
			|| ft_strchr(cmd->args[*index], '\"'))
		{
			tmp = cmd->args[*index];
			cmd->args[*index] = remove_quote(tmp);
			free(tmp);
		}
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
		if (is_redir(token->type) && !cmd->redir_error)
			set_redir(sh, cmd, (char *)token->content);
		else
			fill_arg(sh, cmd-, &arg_no, (char *)token->content);
		token = token->next;
	}
	cmd->args[args_nb] = NULL;
	return (0);
}
