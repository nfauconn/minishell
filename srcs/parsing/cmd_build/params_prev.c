/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_prev.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:20 by noe               #+#    #+#             */
/*   Updated: 2022/08/18 15:41:03 by noe              ###   ########.fr       */
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
		cmd->args_tab[*index] = NULL;
		len = len_until_blank(token);
		tmp = ft_substr(token, 0, len);//tmp = le word (colle a des quotes ou non) qui sera ajoute comme argument
		/*if :
			- on trouve un $identifier PAS ENTRE QUOTES qui a une VAR_VAL
					>field_splitter_expand(cmd, index) --> split chaque arg en content --> lstnew -->lstaddback
						-> multiplier x -1 les quotes!!! 
						-> ajouter chaque string a cmd->args_tab a partir de index
						-> free le split
			else
		*/
		cmd->args_tab[*index] = expand(tmp, sh);//on l expand
		free(tmp);
		if (ft_strchr(cmd->args_tab[*index], '\'')
			|| ft_strchr(cmd->args_tab[*index], '\"'))
		{
			tmp = cmd->args_tab[*index];
			cmd->args_tab[*index] = remove_quote(tmp);
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
	cmd->args_tab = (char **)malloc(sizeof(char *) * (args_nb + 1));
	if (!cmd->args_tab)
		return (1);
	while (token && token->type != '|')
	{
		if (is_redir(token->type) && !cmd->redir_error)
		{
			printf("cmd->redir_error = %d\n", cmd->redir_error);
			set_redir(sh, cmd, (char *)token->content);
		}
		else if (!is_redir(token->type))
			fill_arg(sh, cmd, &arg_no, (char *)token->content);
		token = token->next;
	}
	cmd->args_tab[args_nb] = NULL;
	return (0);
}
