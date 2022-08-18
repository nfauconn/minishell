/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:46:29 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/18 15:41:03 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

static void	builtin_exit_clear(t_sh *sh, unsigned char exit_code)
{
	if (sh->cmd_nb == 1)
		exit_clear_minish(sh, exit_code);
	else
		exit_clear_child(sh, exit_code);
}

static int	ft_atoll_err_main(char *s, long long *nbr, long long *prv)
{
	while (*s >= '0' && *s <= '9')
	{
		*prv = *nbr;
		*nbr = (*nbr * 10) + (*s - '0');
		if (*nbr < *prv)
			return (0);
		s++;
	}
	return (1);
}

static int	ft_atoll_err(char *s, long long *nbr)
{
	int			sign;
	long long	prv;

	*nbr = 0;
	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s != '-' && *s != '+' && !ft_isdigit(*s))
		return (0);
	if (!ft_str_isdigit(s + 1))
		return (0);
	if (!ft_strcmp(s, "-9223372036854775808"))
	{
		*nbr = LLONG_MIN;
		return (1);
	}
	if (*s == '-' || *s == '+')
	{
		sign = -1 * (*s == '-') + (*s == '+');
		s++;
	}
	if (!ft_atoll_err_main(s, nbr, &prv))
		return (0);
	*nbr = *nbr * sign;
	return (1);
}

int	mini_exit(t_sh *sh, t_cmd *cmd)
{
	int			i;
	long long	exit_code;

	i = 0;
	exit_code = 0;
	while (cmd->args_tab[i])
		i++;
	if (i == 1)
		builtin_exit_clear(sh, 0);
	else if (i == 2 && !ft_atoll_err(cmd->args_tab[1], &exit_code))
	{
		error_display("exit", cmd->args_tab[1], ": numeric argument required");
		builtin_exit_clear(sh, 2);
	}
	else if (i > 2)
	{
		error_display("exit", "too many arguments", 0);
		return (1);
	}
	else
	{
		builtin_exit_clear(sh, exit_code);
	}
	return (1);
}
