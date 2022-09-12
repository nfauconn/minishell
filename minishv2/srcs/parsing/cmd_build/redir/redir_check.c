/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:57:11 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/16 09:00:04 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

t_bool	check_access(char *filename, int flag)
{
	if (access(filename, flag) < 0)
	{
		error_display(filename, strerror(errno), 0);
		return (1);
	}
	return (0);
}

static t_bool	check_ambig_value(char *var, t_sh *sh)
{
	char	*value;
	t_bool	ret;
	int		i;

	ret = 0;
	value = var_value(var, ft_strlen(var), sh->env);
	if (!value || !*value)
		ret = 1;
	else
	{
		i = 0;
		while (value[i] && is_blank(value[i]))
			i++;
		if (!value[i])
			ret = 1;
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

t_bool	check_ambig(t_sh *sh, char *token)
{
	token++;
	if (!*token)
		return (0);
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		return (0);
	return (check_ambig_value(token, sh));
}
