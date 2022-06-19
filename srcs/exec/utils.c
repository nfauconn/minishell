/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:38:14 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/19 12:35:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_string_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	*join_path(char const *penv, char const *pexec)
{
	char	*dst;
	size_t	len1;
	size_t	len2;
	size_t	sep;

	len1 = ft_strlen(penv);
	len2 = ft_strlen(pexec);
	sep = penv[len1 - 1] != '/';
	dst = (char *)malloc(sizeof(char)
			* (len1 + len2 + sep + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, penv, len1 + 1);
	if (penv[len1 - 1] != '/')
		dst[len1] = '/';
	ft_strlcpy(dst + len1 + (penv[len1 - 1] != '/'), pexec, len2 + 1);
	return (dst);
}

/*
void grab_command(t_list *token)
{
	t_list *l;
	t_list	*start;

	while (token)
	{
		if (token->type == IN_REDIR || token->type == OUT_REDIR)
		{
			start = token->next->next;
			if (start)
			while (start && !is_redir(*(char *)start->content)
				&& !is_blank(*(char *)start->content) 
				&& !is_separator(*(char *)start->content))
			{
				ft_lstadd_back(&l, ft_lstnew(ft_strdup(start->content)));
				start = start->next;
			}
		}
		else
			start = token->next;
		token = start;
	}
	ft_lstiter(l, display_token_list);
}
*/