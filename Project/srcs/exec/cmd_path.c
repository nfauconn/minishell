/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:06:55 by user42            #+#    #+#             */
/*   Updated: 2024/01/29 13:09:34 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	no_path_in_env(char **envp)
{
	t_bool	ret;
	char	*path_val;
	t_list	*env_lst;
	char	**possible_paths;

	possible_paths = get_path_tab(envp);
	env_lst = ft_strarraytolist(envp);
	path_val = var_value("PATH", 4, env_lst);
	ft_lstclear(&env_lst, free);
	if (!possible_paths || !path_val || ft_strlen(path_val) == 0)
		ret = 1;
	else
		ret = 0;
	free(path_val);
	ft_strarrayclear(&possible_paths);
	return (ret);
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
	dst = malloc(sizeof(char) * (len1 + len2 + sep + 1));
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
		tab[len] = ft_strdup(env->content);
		if (!tab[len])
			return (NULL);
		len++;
		env = env->next;
	}
	tab[len] = NULL;
	return (tab);
}

char	**get_path_tab(char **env)
{
	size_t	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		++i;
	if (env[i])
		return (ft_split(&(env[i][5]), ':'));
	return (NULL);
}
