/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:44:29 by user42            #+#    #+#             */
/*   Updated: 2022/08/06 21:05:51 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_H
# define CLOSE_H

#include "extern_libs.h"
#include "structs.h"

void	close_if_opened(int fd);
void	close_cmd_redirs(t_cmd *cmd);

#endif