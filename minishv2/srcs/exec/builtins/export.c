/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:53:50 by nfauconn          #+#    #+#             */
/*   Updated: 2022/09/10 19:04:11 by nfauconn         ###   ########.fr       */
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

static void	print_env_tab(t_sh *sh, t_cmd *cmd, t_list *env)
{
	char	**tab;
	int		j;
	int		i;
	int		fd_out;

	tab = get_env_tab(env);
	if (!tab)
		return ;
	sort_str_tab(tab);
	j = 0;
	if (sh->cmd_nb == 1 && cmd->redir_out)
		fd_out = handle_redir_out(cmd);
	else
		fd_out = STDOUT_FILENO;
	while (tab[j])
	{
		if (ft_strncmp(tab[j], "_=", 2))
		{
			ft_putstr_fd("declare -x ", fd_out);
			i = 0;
			while (tab[j][i] && tab[j][i] != '=')
				ft_putchar_fd(tab[j][i++], fd_out);
			if (tab[j][i] == '=')
			{
				ft_putstr_fd("=\"", fd_out);
				ft_putstr_fd(&tab[j][i + 1], fd_out);
				ft_putstr_fd("\"", fd_out);
			}
			else
				ft_putstr_fd("\n", fd_out);
		}
		++j;
	}
	ft_strarrayclear(&tab);
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
			if (!l->content)
				return ;
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
		print_env_tab(sh, cmd, sh->env);
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
