/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:58:31 by user42            #+#    #+#             */
/*   Updated: 2022/07/30 01:26:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "extern_libs.h"
# include "structs.h"
# include "exit.h"

char	*perror_and_free(t_input *input, char *s);
void	error_display(char *s1, char *s2, char *s3);
int		exec_perror(char *s1, char *s2);

#endif