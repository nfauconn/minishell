/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:27:49 by mdankou           #+#    #+#             */
/*   Updated: 2022/05/15 19:19:45 by mdankou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list  *search_token(char *token, t_list *env)
{
    int len;

    len = strlen(token);
    while (env)
    {
        if(!strncmp(token, (char *)env->content, len)
            && ((char *)env->content)[len] == '=')
            break ;
        env = env->next;
    }
    return (env);
}


char *var_expand(char *token, t_list *env)
{
    (void)token;
    (void)env;
    return (NULL);
}

