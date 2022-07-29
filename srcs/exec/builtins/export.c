/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/30 00:34:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	sort_str_tab(char **tab)
{
	char	*tmp;
	int		size;
	int		j;
	int		i;

	size = 0;
	while (tab[size])
		size++;
	if (size < 2)
		return ;
	j = -1;
	while (++j < size)
	{
		i = 0;
		while (++i < size)
		{
			if (ft_strcmp(tab[i - 1], tab[i]) > 0)
			{
				tmp = tab[i - 1];
				tab[i - 1] = tab[i];
				tab[i] = tmp;
			}
		}
	}
}

static void	print_env_tab(t_list *env)
{
	char	**tab;
	int		j;
	int		i;

	tab = get_env_tab(env);
	if (!tab)
		return ;
	sort_str_tab(tab);
	j = 0;
	while (tab[j])
	{
		if (ft_strncmp(tab[j], "_=", 2))
		{
			ft_printf("declare -x ");
			i = 0;
			while (tab[j][i] && tab[j][i] != '=')
				ft_printf("%c", tab[j][i++]);
			if (tab[j][i] == '=')
				ft_printf("=\"%s\"\n", &tab[j][i + 1]);
			else
				ft_printf("\n");
		}
		++j;
	}
	ft_strarray_clear(tab);
}

void	do_export(t_list **env, char *assign)
{
	t_list	*l;
	char	*str;
	int		var_len;

	var_len = 0;
	while (assign[var_len] && assign[var_len] != '=')
		++var_len;
	l = (t_list *)(*env);
	while (l)
	{
		str = (char *)l->content;
		if (!ft_strncmp(assign, str, var_len) && (str[var_len] == '='
				|| str[var_len] == '\0'))
		{
			l->content = ft_strdup(assign);
			free(str);
			break ;
		}
		l = l->next;
	}
	if (!l)
		ft_lstadd_back(env, ft_lstnew(ft_strdup(assign)));
}

static int	is_valid_identifier(char *str)
{
	size_t	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		++i;
	}
	return (1);
}

int	mini_export(t_sh *sh, t_cmd *cmd)
{
	char	**var_assigns;
	int		status;
	size_t	j;

	var_assigns = cmd->args;
	j = 1;
	status = 0;
	if (!var_assigns || !var_assigns[j])
		print_env_tab(sh->env);
	j = 1;
	while (var_assigns && var_assigns[j])
	{
		if (is_valid_identifier(var_assigns[j]))
			do_export(&sh->env, var_assigns[j]);
		else
		{
			ft_printerror("minish: export: `%s': " \
				"not a valid identifier\n", var_assigns[j]);
			status = 1;
		}
		++j;
	}
	return (status);
}
