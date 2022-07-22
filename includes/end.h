/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:16:07 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/20 20:06:40 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef END_H
# define END_H

# include "extern_libs.h"
# include "structs.h"

void	clear(t_input *input, t_sh *sh);
void	clear_input(t_input *input);
void	clear_sh(t_sh *sh);
void	exit_clear(t_sh *sh, unsigned int exit_code);

#endif
