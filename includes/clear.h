/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:25:19 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 00:58:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAR_H
# define CLEAR_H

# include "extern_libs.h"
# include "structs.h"
# include "close.h"

void	clear_input(t_input *input);
void	clear_sh(t_sh *sh);
void	clear_cmd_list(t_cmd *cmd);

#endif