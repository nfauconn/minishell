/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:58:31 by user42            #+#    #+#             */
/*   Updated: 2022/08/11 22:11:31 by nfauconn         ###   ########.fr       */
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
void	perror_exit(t_sh *sh, char *s1, char *s2, unsigned char exit_code);

#endif