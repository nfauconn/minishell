/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearexit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:16:07 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/28 13:22:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAREXIT_H
# define CLEAREXIT_H

# include "extern_libs.h"
# include "structs.h"

void	clear_input(t_input *input);
void	reset_sh(t_sh *sh);
void	clear_cmd_list(t_cmd *cmd);
void	exit_subprocess(t_sh *sh, unsigned char exit_code);
void	exit_clear_process(t_sh *sh, unsigned char exit_code);

#endif
