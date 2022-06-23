/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_free_old.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:17:42 by user42            #+#    #+#             */
/*   Updated: 2022/06/23 12:20:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace_and_free(void **prev_content, void *new_content)
{
	void	*tmp;

	tmp = *prev_content;
	*prev_content = new_content;
	free(tmp);
}
