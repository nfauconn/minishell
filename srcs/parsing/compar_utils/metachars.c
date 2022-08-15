/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:55:34 by user42            #+#    #+#             */
/*   Updated: 2022/08/15 01:02:45 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	is_sep_operator(char c)
{
	return (c == '|');
}

bool	is_redir(char c)
{
	return (c == '<' || c == '>');
}

bool	is_operator(char c)
{
	return (is_sep_operator(c) || is_redir(c));
}

bool	is_metachar(char c)
{
	return (is_blank(c) || is_redir(c) || is_sep_operator(c));
}
