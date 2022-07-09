/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:01:13 by user42            #+#    #+#             */
/*   Updated: 2022/07/08 13:17:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define INTERACTIVE 0
# define SH_PROCESS 1
# define CHILD_PROCESS 2

# include "extern_libs.h"

void	signal_catching_mode(int mode);

#endif