/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:01:13 by user42            #+#    #+#             */
/*   Updated: 2022/07/12 18:58:13 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define INTERACTIVE 56
# define SH_PROCESS 7777
# define CHILD_PROCESS 9999

# include "extern_libs.h"

void	signal_catching_mode(int mode);

#endif