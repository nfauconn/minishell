/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:41:54 by user42            #+#    #+#             */
/*   Updated: 2022/07/08 13:21:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_last_status(t_sh *sh)
{
	char	*tmp;

	if (!sh->last_status_str)
		sh->last_status_str = ft_itoa(sh->last_status);
	else
	{
		tmp = sh->last_status_str;
		sh->last_status_str = ft_itoa(sh->last_status);
		free(tmp);
	}
	return (sh->last_status_str);
}
