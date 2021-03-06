/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:06:55 by user42            #+#    #+#             */
/*   Updated: 2022/07/31 20:09:24 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*join_path(char const *penv, char const *pexec)
{
	char	*dst;
	size_t	len1;
	size_t	len2;
	size_t	sep;

	len1 = ft_strlen(penv);
	len2 = ft_strlen(pexec);
	sep = penv[len1 - 1] != '/';
	dst = (char *)malloc(sizeof(char) * (len1 + len2 + sep + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, penv, len1 + 1);
	if (penv[len1 - 1] != '/')
		dst[len1] = '/';
	ft_strlcpy(dst + len1 + (penv[len1 - 1] != '/'), pexec, len2 + 1);
	return (dst);
}

int	find_path(t_cmd *cmd, char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		cmd->path = join_path(paths[i], cmd->name);
		if (!cmd->path)
			return (0);
		if (access(cmd->path, X_OK) != -1)
			return (1);
		free(cmd->path);
		cmd->path = NULL;
		i++;
	}
	return (0);
}

char	**get_env_tab(t_list *env)
{
	size_t	len;
	char	**tab;

	len = ft_lstsize(env);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	len = 0;
	while (env)
	{

		tab[len] = ft_strdup(env->content);
		if (!tab[len])
			return (NULL);
		len++;
		env = env->next;
	}
	tab[len] = NULL;
	return (tab);
}

char	**get_path_tab(t_list *env)
{
	while (env && ft_strncmp(env->content, "PATH=", 5) )
		env = env->next;
	if (env)
		return (ft_split(env->content + 5, ':'));
	return (NULL);
}
