/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou < mdankou@student.42.fr >          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:51:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/05 17:17:43 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	pwd with no options (and no arguments)
*	@return 0 Successful completion. >0 An error occurred.
*/
int	mini_pwd(t_sh *sh, t_cmd *cmd)
{
	char	*name;

	(void)sh;
	(void)cmd;
	name = getcwd(NULL, 0);
	if (!name)
	{
		error_display("pwd", strerror(errno));
		return (errno);
	}
	printf("%s\n", name);
	free(name);
	return (0);
}
