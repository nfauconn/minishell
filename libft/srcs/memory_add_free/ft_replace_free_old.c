/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_free_old.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:17:42 by user42            #+#    #+#             */
/*   Updated: 2022/06/23 15:35:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace_free_old(void **prev_content, void *new_content)
{
	void	*tmp;

	if (prev_content)
	{
		tmp = *prev_content;
		*prev_content = new_content;
		free(tmp);
	}
}