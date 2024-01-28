/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:01:22 by noe               #+#    #+#             */
/*   Updated: 2022/08/18 14:21:44 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*contains_quotes(char *str)
{
	return (ft_strchr(str, '\'' || ft_strchr(str, '\"')));
}

char	*contains_blanks(char *str)
{
	return (ft_strchr(str, ' ' || ft_strchr(str, '\t')));
}
