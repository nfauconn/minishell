/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:18:20 by noe               #+#    #+#             */
/*   Updated: 2022/08/18 18:42:24 by mdankou          ###   ########.fr       */
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

static void field_splitter_expand(char *str, t_cmd *cmd)
{
	int		i;
	int		k;
	char	*content;
	t_list *tmp;

	while (*str)
	{
		while (*str && is_blank(*str))
			++str;
		i = 0;
		if (!*str)
			break ;
		while (str[i] && !is_blank(str[i]))
			++i;
		content = ft_substr(str, 0, i);
		tmp = ft_lstnew(content);
		/*if (!tmp || !tmp->content)
		{
			ft_lstclear(&cmd->args_lst, free);
		}
		*/
		k = -1;
		while (content[++k])
			if (content[k])
				content[k] = content[k] * (-1);
		ft_lstadd_back(&cmd->args_lst, tmp);
		str += i;
	}
}

static char	*search_id_without_quote(char *str)
{
	char *dollar;
	char *quote;

	dollar = ft_strchr(str, '$');
	dollar = ft_strchr(str, '$');
	if (!dollar)
		return (NULL);
	if ((dollar == str || !is_quote(*(dollar - 1)))
		&& is_identifier(dollar[1]))
	{
		return (dollar);
	}
	return (NULL);
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
		content = expand(tmp, sh);
		printf("content = %s\n", content);
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
		if (search_id_without_quote(tmp))
		{
			free(tmp);
			field_splitter_expand(content, cmd);
		}
		else
		{
			free(tmp);
			if (ft_strchr(content, '\'')
				|| ft_strchr(content, '\"'))
			{
				tmp = content;
				content = remove_quote(tmp);
				free(tmp);
			}
			ft_lstadd_back(&cmd->args_lst, ft_lstnew(content));
		}	
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
