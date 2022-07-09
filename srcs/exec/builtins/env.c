/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/08 13:20:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
*	env with no options or arguments
*/
int	mini_env(t_sh *sh, t_cmd *cmd)
{
	t_list	*l;

	(void)cmd;
	l = sh->env;
	while (l)
	{
		printf("%s\n", (char *)l->content);
		l = l->next;
	}
	return (0);
}
