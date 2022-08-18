/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:20 by noe               #+#    #+#             */
/*   Updated: 2022/08/18 23:48:37 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	reset_quotes_to_ascii(t_list *cmd_args)
{
	char	*content;

	while (cmd_args)
	{
		content = (char *)cmd_args->content;
		while (content && *content)
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

static t_bool	fill_arg(t_sh *sh, t_list **args_list, char *token)
{
	size_t	len;
	char	*tmp;
	char	*content;

	len = 0;
	while (*token)
	{
		len = len_until_blank(token);
		tmp = ft_substr(token, 0, len);
		content = expand(tmp, sh);
//		printf("content = %s\n", content);
		free(tmp);
		tmp = content;
		content = remove_quote(tmp);
		free(tmp);
		ft_lstadd_back(args_list, ft_lstnew(content));
		token += len;
		while (is_blank(*token))
			token++;
	}
	return (0);
}

t_bool	set_cmd_params(t_sh *sh, t_list *token, t_cmd *cmd)
{
	t_list	*args_lst;

	args_lst = NULL;
	while (token && token->type != '|')
	{
		if (is_redir(token->type))
		{
			if (!cmd->redir_error)
				set_redir(sh, cmd, (char *)token->content);
		}
		else
			fill_arg(sh, &args_lst, (char *)token->content);
		token = token->next;
	}
	reset_quotes_to_ascii(args_lst);
	cmd->args = ft_lsttostrarray(args_lst);
	ft_lstclear(&args_lst, free);
	return (0);
}
