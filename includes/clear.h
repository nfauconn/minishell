/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:25:19 by user42            #+#    #+#             */
/*   Updated: 2022/08/19 01:15:44 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAR_H
# define CLEAR_H

# include "extern_libs.h"
# include "structs.h"

void	clear_input(t_input *input);
void	clear_sh(t_sh *sh);
void	clear_cmd_list(t_cmd **cmd);

#endif