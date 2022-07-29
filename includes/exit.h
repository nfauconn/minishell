/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:24:54 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 01:07:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "extern_libs.h"
# include "structs.h"
# include "clear.h"
# include "error.h"

void	exit_clear_minish(t_sh *sh, unsigned char exit_code);
void	exit_clear_child(t_sh *sh, unsigned char exit_code);

#endif