/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:52:13 by mdankou           #+#    #+#             */
/*   Updated: 2022/07/09 17:46:20 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "extern_libs.h"
# include "structs.h"
# include "error.h"

int		mini_exit(t_sh *sh, t_cmd *cmd);
int		mini_cd(t_sh *sh, t_cmd *cmd);
int		mini_echo(t_sh *sh, t_cmd *cmd);
int		mini_env(t_sh *sh, t_cmd *cmd);
int		mini_export(t_sh *sh, t_cmd *cmd);
void	do_export(t_list **env, char *assign);
int		mini_pwd(t_sh *sh, t_cmd *cmd);
int		mini_unset(t_sh *sh, t_cmd *cmd);

#endif
