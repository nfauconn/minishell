/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:06:55 by user42            #+#    #+#             */
/*   Updated: 2022/07/21 19:51:03 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	find_path(t_cmd *cmd, char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		cmd->path = join_path(paths[i], cmd->name);
		if (!cmd->path)
			break ;
		if (access(cmd->path, X_OK) != -1)
			return (1);
		free(cmd->path);
		i++;
	}
	return (0);
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
	dst = (char *)malloc(sizeof(char) * (len1 + len2 + sep + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, penv, len1 + 1);
	if (penv[len1 - 1] != '/')
		dst[len1] = '/';
	ft_strlcpy(dst + len1 + (penv[len1 - 1] != '/'), pexec, len2 + 1);
	return (dst);
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
		tab[len++] = ft_strdup(env->content);
		if (!tab[len])
			break ;
		env = env->next;
	}
	tab[len] = NULL;
	return (tab);
}

//Line 84: DO WE HAVE THE RIGHT TO DO THAT LOL, as bash find a path anyways
char	**get_path_tab(t_list *env)
{
	char	**tab;

	while (env && ft_strncmp(env->content, "PATH=", 5))
		env = env->next;
	if (!env)
	{
		tab = ft_split(
				"/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin", ':');
		return (tab);
	}
	return (ft_split(env->content + 5, ':'));
}
