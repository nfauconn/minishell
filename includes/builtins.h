/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:13 by mdankou           #+#    #+#             */
/*   Updated: 2022/05/30 14:27:34 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "libft.h"

int	builtin_pwd(char **args);
int	builtin_cd(char **args);
int	builtin_echo(char **args);
int	builtin_env(void *env);
int	builtin_unset(t_list **env, char **var_name);
int	builtin_export(t_list **env, char **var_assign);

#endif
