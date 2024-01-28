/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:58:31 by user42            #+#    #+#             */
/*   Updated: 2022/08/19 16:03:54 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "extern_libs.h"
# include "structs.h"
# include "exit.h"

t_bool	sh_perror(char *s);
t_bool	error_display(char *s1, char *s2, char *s3);
t_bool	exec_perror(char *s1, char *s2);
void	perror_exit_clear(t_sh *sh, char *s1, char *s2, uint8_t exit_code);

#endif