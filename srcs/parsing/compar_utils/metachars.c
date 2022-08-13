/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:55:34 by user42            #+#    #+#             */
/*   Updated: 2022/08/14 00:37:58 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool	is_sep_operator(char c)
{
	return (c == '|');
}

bool	is_rediroperator(char c)
{
	return (c == '<' || c == '>');
}

bool	is_operator(char c)
{
	return (is_sep_operator(c) || is_rediroperator(c));
}

bool	is_metachar(char c)
{
	return (is_blank(c) || is_rediroperator(c) || is_sep_operator(c));
}
