/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:20 by noe               #+#    #+#             */
/*   Updated: 2022/08/18 17:00:00 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	reset_quotes_to_ascii(t_list *cmd_args)
{
	char	*content;

	while (cmd_args)
	{
		content = (char *)cmd_args->content;
		while (*content)
		{
			if (*content < 0)
				*content *= -1;
			content++;
		}
		cmd_args = cmd_args->next;
	}
}

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

static t_bool	fill_arg(t_sh *sh, t_cmd *cmd, char *token)
{
	size_t	len;
	char	*tmp;
	char	*content;

	len = 0;
	while (*token)
	{
		len = len_until_blank(token);
		tmp = ft_substr(token, 0, len);//tmp = le word (colle a des quotes ou non) qui sera ajoute comme argument
		/*if :
			- on trouve un $identifier PAS ENTRE QUOTES qui a une VAR_VAL
					>field_splitter_expand(cmd, index) 
						-> split chaque arg en content 	
							-> multiplier x -1 les quotes!!! 
							-> remove quotes ??
							-> lstnew -->lstaddback
						-> free le split
			else
		*/
		content = expand(tmp, sh);
		free(tmp);
		if (ft_strchr(content, '\'')
			|| ft_strchr(content, '\"'))
		{
			tmp = content;
			content = remove_quote(tmp);
			free(tmp);
		}
		ft_lstadd_back(&cmd->args_lst, ft_lstnew(content));
		token += len;
		while (is_blank(*token))
			token++;
	}
	return (0);
}

t_bool	set_cmd_params(t_sh *sh, t_list *token, t_cmd *cmd)
{
	while (token && token->type != '|')
	{
		if (is_redir(token->type))
		{
			if (!cmd->redir_error)
				set_redir(sh, cmd, (char *)token->content);
		}
		else
			fill_arg(sh, cmd, (char *)token->content);
		token = token->next;
	}
	reset_quotes_to_ascii(cmd->args_lst);
	cmd->args_tab = ft_lsttostrarray(cmd->args_lst);
	return (0);
}
