/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:20 by noe               #+#    #+#             */
/*   Updated: 2022/09/06 18:20:53 by mdankou          ###   ########.fr       */
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
			if (*content == -('\'') || *content == -('\"'))
				*content *= -1;
			content++;
		}
		cmd_args = cmd_args->next;
	}
}

void	set_quotes_to_negative(char *content)
{
	char	quote;

	quote = 0;
	while (content && *content)
	{
		while (*content && !is_quote(*content))
			++content;
		quote = *content;
		if (!*content)
			return ;
		if (!ft_strchr(content + 1, quote))
		{
			*content *= -1;
			return ;
		}
		while (*(++content) && quote != *content)
		{
			if ((quote == '\"' && *content == ('\''))
				|| (quote == '\'' && *content == ('\"')))
					*content *= -1;
		}
		if (quote == *content)
			++content;
		quote = 0;
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
			if (s[i] == quote)
				i++;
		}
		else if (is_blank(s[i]))
			return (i);
		else
			i++;
	}
	return (i);
}

static t_bool	fill_arg(t_list **args_list, char *token)
{
	size_t	len;
	char	*arg_w_quotes;
	char	*arg;

	len = 0;
	while (is_blank(*token))
		token++;
	while (*token)
	{
		printf("*token = %s\n", token);
		len = len_until_blank(token);
		arg_w_quotes = ft_substr(token, 0, len);
		printf("arg_w_quotes = %s\n", arg_w_quotes);
		arg = remove_quote(arg_w_quotes);
		printf("arg after removing quotes = %s\n", arg);
		free(arg_w_quotes);
		ft_lstadd_back(args_list, ft_lstnew(arg));
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
	while (token && token->type != '|' && cmd->redir_error != 1)
	{
		if (is_redir(token->type))
			set_redir(sh, cmd, (char *)token->content);
		else
		{
			ft_replacefree(&token->content, expand(token->content, sh));
//			printf("expanded token->content = |%s|\n", (char *)token->content);
			set_quotes_to_negative((char *)token->content);
//			printf("escaped_quote token->content = |%s|\n", (char *)token->content);
			fill_arg(&args_lst, (char *)token->content);
		}
		token = token->next;
	}
	while (token && token->type != '|' && cmd->redir_in.heredoc_ctrlc == 0)
	{
		if (!ft_strncmp((char *)token->content, "<<", 2))
			set_redir(sh, cmd, (char *)token->content);
		token = token->next;
	}
	/*
	if (cmd->redir_error || cmd->redir_in.heredoc_ctrlc)
	{
		ft_lstclear(&args_lst, free);
		return (1);
	}
	*/
	reset_quotes_to_ascii(args_lst);
	cmd->args = ft_lsttostrarray(args_lst);
	ft_lstclear(&args_lst, free);
	return (0);
}
