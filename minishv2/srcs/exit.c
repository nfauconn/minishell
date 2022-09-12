/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:14:07 by user42            #+#    #+#             */
/*   Updated: 2022/08/19 16:18:40 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	exit_clear_child(t_sh *sh, uint8_t exit_code)
{
	clear_sh(sh);
	exit(exit_code);
}

void	exit_clear_minish(t_sh *sh, uint8_t exit_code)
{
	ft_printerror("exit\n");
	clear_sh(sh);
	exit(exit_code);
}
