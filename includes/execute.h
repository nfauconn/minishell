/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:22:26 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/07 17:53:27 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

typedef struct s_cmdinfo
{
	int				redir[2];
	struct s_cmdinfo	*next;
}	t_cmdinfo;

void	apply_redirections(t_list *token_list);

#endif