/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:25:19 by user42            #+#    #+#             */
/*   Updated: 2022/09/10 16:56:26 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAR_H
# define CLEAR_H

# include "extern_libs.h"
# include "structs.h"

void	clear_input(t_input *input);
void	clear_sh(t_sh *sh);
void	clear_cmd_list(t_cmd **cmd);
void	clear_cmd(t_cmd *cmd);
void	clear_redir_in(t_redir **redir_in);

#endif