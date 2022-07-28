/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:01:13 by user42            #+#    #+#             */
/*   Updated: 2022/07/28 19:47:49 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define INTERACTIVE 0
# define PARENT_PROCESS 1
# define CHILD_PROCESS 2
# define HEREDOC 3

# include "extern_libs.h"

//extern unsigned char	g_last_status;

void	signal_catching_mode(int mode);

#endif