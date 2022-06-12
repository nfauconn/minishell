/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:00:14 by user42            #+#    #+#             */
/*   Updated: 2022/06/11 10:11:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_mode(char *(*f)(char *, char *), char **to_free, char *to_add)
{
	char	*tmp;

	if (!to_free)
		return ;
	tmp = *to_free;
	*to_free = (f)(tmp, to_add);
	free(tmp);
}
