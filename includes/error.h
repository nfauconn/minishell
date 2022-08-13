/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:58:31 by user42            #+#    #+#             */
/*   Updated: 2022/08/13 22:32:57 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "extern_libs.h"
# include "structs.h"
# include "exit.h"

bool	sh_perror(char *s);
bool	error_display(char *s1, char *s2, char *s3);
bool	exec_perror(char *s1, char *s2);
void	perror_exit(t_sh *sh, char *s1, char *s2, unsigned char exit_code);

#endif