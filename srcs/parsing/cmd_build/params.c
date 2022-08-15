
#include "parse.h"

size_t	len_until_blank(char *s)
{
	size_t	i;
	char	quote;

	i = 0;
	while (s && s[i])
	{
		if (is_quote(s[i]))
		{
			quote = s[i++];
			while (s[i] != quote)
				i++;
			i++;
		}
		else if (is_blank(s[i]))
			return (i);
		else
			i++;
	}
	return (i);
}

static bool	fill_arg(t_sh *sh, char **arg_tab, size_t *index, char *token)
{
	size_t	len;
	char	*tmp;

	len = 0;
	while (*token)
	{
		arg_tab[*index] = NULL;
		len = len_until_blank(token);
		tmp = ft_substr(token, 0, len);
		arg_tab[*index] = expand(tmp, sh);
		free(tmp);
		if (!arg_tab[*index])
			return (1);
		(*index)++;
		token += len;
		while (is_blank(*token))
			token++;
	}
	return (0);
}

bool	set_cmd_params(t_sh *sh, t_list *token, t_cmd *cmd)
{
	size_t	args_nb;
	size_t	arg_no;

	args_nb = get_args_nb(token);
	arg_no = 0;
	cmd->args = (char **)malloc(sizeof(char *) * (args_nb + 1));
	if (!cmd->args)
		return (1);
	while (token && token->type != '|')
	{
		if (is_redir(token->type) && !cmd->redir_error)
			set_redir(sh, cmd, (char *)token->content);
		else if (fill_arg(sh, cmd->args, &arg_no, (char *)token->content))
		{
 			clear_tab(cmd->args, arg_no);
			free(cmd);
			return (1);
		}
		token = token->next;
	}
	cmd->args[arg_no] = NULL;
	return (0);
}
