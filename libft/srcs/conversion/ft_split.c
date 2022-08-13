/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:58:22 by nfauconn          #+#    #+#             */
/*   Updated: 2022/08/13 23:02:09 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	line_nb(char const *s, char c)
{
	int		i;
	int		line_nb;

	i = 0;
	while (s[i] && (s[i] == c))
		i++;
	line_nb = 0;
	while (s[i])
	{
		while (s[i] && (s[i] != c))
			i++;
		line_nb++;
		while (s[i] && (s[i] == c))
			i++;
	}
	return (line_nb);
}

static int	len_until_sep(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	clear_tab(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*fill_tab(const char *s, int *i, char c)
{
	char	*tab_line;
	int		j;

	tab_line = malloc(sizeof(char) * (len_until_sep(s + *i, c) + 1));
	if (!s)
		return (NULL);
	j = 0;
	while (s[*i] && s[*i] != c)
		tab_line[j++] = s[(*i)++];
	tab_line[j] = '\0';
	return (tab_line);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		index;
	int		i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (line_nb(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	index = 0;
	while (s[i] && (index < line_nb(s, c)))
	{
		while (s[i] && s[i] == c)
			i++;
		tab[index] = fill_tab(s, &i, c);
		if (!tab[index])
		{	
			clear_tab(tab, index);
			return (NULL);
		}
		index++;
	}
	tab[index] = NULL;
	return (tab);
}
