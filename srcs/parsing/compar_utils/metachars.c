/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:55:34 by user42            #+#    #+#             */
/*   Updated: 2022/08/06 21:43:45 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	is_sep_operator(char c)
{
	return (c == '|');
}

t_bool	is_rediroperator(char c)
{
	return (c == '<' || c == '>');
}

t_bool	is_operator(char c)
{
	return (is_sep_operator(c) || is_rediroperator(c));
}

t_bool	is_metachar(char c)
{
	return (is_blank(c) || is_rediroperator(c) || is_sep_operator(c));
}
