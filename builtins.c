/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:41:03 by mdankou           #+#    #+#             */
/*   Updated: 2022/05/11 17:38:11 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <libft.h>

/*
Suppose char **args est termine par un NULL
*/

int pwd(char **args)
{
	char	*name;

	(void)args;
	name = getcwd(NULL, 0);
	if (!name)
	{
		perror("pwd");
		return (errno);
	}
	printf("%s\n", name);
	return (0);
}

int cd(char **args)
{
	DIR*	dir;

	if (!args[0])
		errno = EINVAL;
	else if (args[1])
		errno = E2BIG;
	else
	{
		dir = opendir(args[0]);
		if (!dir)
			perror("pwd");
		else
			chdir(args[0]);
	}
	return (errno);
}

int echo(char **args)
{
	int		nl_flag;
	size_t	j;
	size_t	i;

	j = 0;
	nl_flag = 0;
	while (args[j])
	{
		if (args[j][0] == '-')
		{
			i = 1;
			while (args[j][i] == 'n')
				++i;
			if (args[j][i] != '\0')
				break;
			nl_flag = 1;
		}
		else
			break;
		++j;
	}
	while (args[j])
	{
		printf("%s", args[j]);
			if (args[j + 1])
				printf(" ");
		++j;
	}
	if (!nl_flag)
		printf("\n");
	return (0);
}

int env(void *env)
{
	t_list *l;

	l = (t_list *)env;
	while (l)
	{
		printf("%s\n", (char *)l->content);
		l = l->next;
	}
	return (0);
}

/*False: Incomplete*/

/*Faire une fontion search_previous pourrait etre une bonne idee*/

int unset(void *env, char **var_name)
{
	size_t	j;
	t_list	*l;
	t_list	*elm;
	char	*str;
	int	var_len;

	j = 0;
	l = (t_list *)env;
	str = (char *)l->content;
	var_len = strlen(var_name[j]);
	if (!((t_list *)env)->next && !ft_strncmp(var_name[j], str, var_len)
		&& str[var_len] == '\0')
	{
		ft_lstclear((t_list **)&env, free);
		return (0);
	}
	while (var_name[j])
	{
		l = (t_list *)env;
		while (l)
		{
			elm = l->next;
			if (elm)
			{
				str = (char *)elm->content;
				var_len = strlen(var_name[j]);
				if (!ft_strncmp(var_name[j], str, var_len)
					&& str[var_len] == '\0')
				{
					break;	
				}
			}
			l = l->next;
		}
		l->next = elm->next;
		ft_lstdelone(elm, free);
		++j;
	}
	return (0);
}

int export(void *env, char **var_assign)
{
	size_t	j;
	t_list	*l;
	char	*str;
	int	var_len;

	j = 0;
	while (var_assign[j])
	{
		l = (t_list *)env;
		while (l)
		{
			str = (char *)l->content;
			var_len = strlen(var_assign[j]);
			if (!ft_strncmp(var_assign[j], str, var_len)
				&& str[var_len] == '\0')
			{
				l->content = ft_strdup(str);
				break;
			}
			l = l->next;
		}
		if (!l)
			ft_lstadd_back((t_list **)&env, ft_lstnew(ft_strdup(str)));
		++j;
	}
	return (0);

}
