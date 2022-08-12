/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:19:46 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/12 19:51:57 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static t_bool	check_ambig_value(char *var, t_sh *sh)
{
	char	*value;
	t_bool	ret;
	int		i;

	ret = 0;
	value = var_value(var, ft_strlen(var), sh->env);
	if (!value)
		ret = 1;
	else
	{
		i = 1;
		while (value[i] && is_blank(value[i]))
			i++;
		while (value[i] && !is_blank(value[i]))
			i++;
		while (value[i] && is_blank(value[i]))
			i++;
		if (value[i])
			ret = 1;
		free(value);
	}
	return (ret);
}

t_bool	is_ambiguous_redir(t_sh *sh, char *token)
{
	t_bool	ret;

	token++;
	if (!*token)
		return (0);
	ret = 0;
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
	{
		
		return (0);
	}
	ret = check_ambig_value(token, sh);
	return (ret);
}
