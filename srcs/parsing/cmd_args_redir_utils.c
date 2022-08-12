#include "parse.h"

size_t	arg_len(char *s)
{
	size_t	i;
	char	quote;

	i = 0;
	while (s && s[i] && !is_operator(s[i]))
	{
		if (is_quote(s[i]))
		{
			quote = s[i];
			while (s[i] != quote)
				i++;
		}
		if (is_blank(s[i]))
			return (i);
		i++;
	}
	return (i);
}

size_t	get_args_nb(t_list *token)
{
	char	quote;
	size_t	count;
	char	*content;
	size_t	i;

	count = 1;
	while (token && !is_sep_operator(token->type))
	{
		if (!is_rediroperator(token->type))
		{
			count++;
			content = (char *)token->content;
			i = 0;
			while (content[i])
			{
				if (is_quote(content[i]))
				{
					quote = content[i];
					i++;
					while (content[i] != quote)
						i++;
				}
				if (is_blank(content[i]))
				{
					count++;
					while (is_blank(content[i]))
						i++;
				}
				else
					i++;
			}
		}
		token = token->next;
	}
	return (count);
}

void	clear_tab(char **tab, int index)
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
