/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:41:54 by user42            #+#    #+#             */
/*   Updated: 2022/06/26 22:42:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_last_exit_code(t_sh *sh)
{
	char	*tmp;

	if (!sh->last_exit_code_str)
		sh->last_exit_code_str = ft_itoa(sh->last_exit_code);
	else
	{
		tmp = sh->last_exit_code_str;
		sh->last_exit_code_str = ft_itoa(sh->last_exit_code);
		free(tmp);
	}
	return (sh->last_exit_code_str);
}
