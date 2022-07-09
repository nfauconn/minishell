/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:58:31 by user42            #+#    #+#             */
/*   Updated: 2022/07/08 13:26:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "extern_libs.h"
# include "minishell.h"
# include "structs.h"

char	*perror_and_free(t_input *input, char *s);
void	error_display(char *s1, char *s2);
void	error_exit(char *cmd_name, int8_t error_code);
int		exec_error(char *s1, char *s2);

#endif