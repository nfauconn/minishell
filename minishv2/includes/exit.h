/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:24:54 by user42            #+#    #+#             */
/*   Updated: 2022/08/19 16:18:40 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "extern_libs.h"
# include "structs.h"
# include "clear.h"
# include "error.h"

void	exit_clear_minish(t_sh *sh, uint8_t exit_code);
void	exit_clear_child(t_sh *sh, uint8_t exit_code);

#endif