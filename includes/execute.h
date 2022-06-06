/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:22:26 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/06 17:01:07 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

typedef struct s_cmdinfo
{
	int				redir[2];
	struct s_cmd	*next;
}	t_cmdinfo;

#endif