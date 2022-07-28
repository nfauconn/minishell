/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:16:07 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/27 22:59:21 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef END_H
# define END_H

# include "extern_libs.h"
# include "structs.h"

void	reset_input(t_sh *sh, t_input *input);
void	clear_input(t_input *input);
void	clear_cmd_list(t_cmd *cmd);
void	exit_clear(t_sh *sh, unsigned int exit_code);

#endif
