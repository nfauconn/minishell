/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:13 by mdankou           #+#    #+#             */
/*   Updated: 2022/05/16 20:01:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	pwd(char **args);
int	cd(char **args);
int	echo(char **args);
int	env(void *env);
int	unset(void *env, char **var_name);
int	export(void *env, char **var_assign);

#endif
