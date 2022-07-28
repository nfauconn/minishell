/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitclear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:14:07 by user42            #+#    #+#             */
/*   Updated: 2022/07/28 20:25:44 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clearexit.h"

/* void	exit_subprocess(t_sh *sh, unsigned char exit_code)
{
//	(void)sh;
	clear_cmd_list(sh->cmd_list);
	reset_sh(sh);
	exit(exit_code);
} */

void	exit_clear_process(t_sh *sh, unsigned char exit_code)
{
	(void)sh;

	ft_printerror("exit\n");
	reset_sh(sh);
	exit(exit_code);
}
