/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:13 by mdankou           #+#    #+#             */
/*   Updated: 2022/05/11 15:53:58 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int pwd(char **args);
int cd(char **args);
int echo(char **args);
int env(void *env);
int unset(void *env, char **var_name);
int export(void *env, char **var_assign);

#endif
