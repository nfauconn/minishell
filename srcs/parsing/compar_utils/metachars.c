/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:55:34 by user42            #+#    #+#             */
/*   Updated: 2022/08/16 09:03:52 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	is_sep_operator(char c)
{
	return (c == '|');
}

t_bool	is_redir(char c)
{
	return (c == '<' || c == '>');
}

t_bool	is_operator(char c)
{
	return (is_sep_operator(c) || is_redir(c));
}

t_bool	is_metachar(char c)
{
	return (is_blank(c) || is_redir(c) || is_sep_operator(c));
}

t_bool	is_doll_then_quote(char *s)
{
	return (s[0] == '$' && s[1] && is_quote(s[1]));
}