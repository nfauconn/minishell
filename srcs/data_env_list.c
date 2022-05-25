/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:15:23 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/25 15:16:31 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_list(char **env)
{
	int		i;
	int		len;
	t_list	*env_list;
	t_list	*new;

	len = 0;
	while (env[len])
		len++;
	env_list = NULL;
	i = 0;
	while (env[i])
	{
		new = (t_list *)malloc(sizeof(t_list));
	 	new->content = ft_strdup(env[i]);
		new->next = NULL;
		ft_lstadd_back(&env_list, new);
		i++;
	}
	return (env_list);
}