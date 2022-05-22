/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/22 18:54:30 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(void *env)
{
	t_list	*l;

	l = (t_list *)env;
	while (l)
	{
		printf("%s\n", (char *)l->content);
		l = l->next;
	}
	return (0);
}
