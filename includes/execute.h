/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:22:26 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/14 18:29:05 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_cmd
{
	char			**cmd_tab;
	size_t			index;
	int				redir[2];
	int				in_redir_type;
	int				out_redir_type;
	struct s_cmd	*next;
}	t_cmd;

void	cmd_redirections(t_cmd *cmd, t_list *token);
int		exec_error(char *s1, char *s2);

#endif