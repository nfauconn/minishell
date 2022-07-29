/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:14:07 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 01:02:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	exit_clear_child(t_sh *sh, unsigned char exit_code)
{
	clear_sh(sh);
	exit(exit_code);
}

void	exit_clear_minish(t_sh *sh, unsigned char exit_code)
{
	ft_printerror("exit\n");
	clear_sh(sh);
	exit(exit_code);
}
