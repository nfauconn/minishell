/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_free_old.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:11:07 by nfauconn          #+#    #+#             */
/*   Updated: 2022/07/12 21:12:23 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace_free_old(void **old, void *new)
{
	void	*tmp;

	if (old)
	{
		tmp = *old;
		*old = new;
		free(tmp);
	}
}
