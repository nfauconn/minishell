/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:44:29 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 01:07:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_H
# define CLOSE_H

#include "extern_libs.h"
#include "structs.h"

void	close_if_no_std(int fd);
void	close_cmd_redirs(t_cmd *cmd);

#endif