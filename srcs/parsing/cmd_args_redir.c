
#include "parse.h"

static t_bool	fill_arg(t_sh *sh, char **args, size_t *i, char *token)
{
	size_t	len;
	char	*tmp;
//	char	*new_val;

	len = 0;
	while (*token)
	{
		args[*i] = NULL;
		len = arg_len(token);
		tmp = ft_substr(token, 0, len);
/* 		new_val = NULL;
		expand(tmp, &new_val, sh);
 */
		args[*i] = expand(tmp, sh);
		free(tmp);
		if (!args[*i])
			return (1);
//		args[*i] = ft_strdup(new_val);
//		free(new_val);
//		(void)sh;
//		args[*i] = ft_substr(token, 0, len);
//		printf("args[%zu] = %p\n", *i, args[*i]);

		(*i)++;
		token += len;
		while (is_blank(*token))
			token++;
	}
	return (0);
}

t_bool	get_args_and_redir(t_sh *sh, t_list *token, t_cmd *cmd)
{
	size_t	args_nb;
	size_t	i;
	t_bool	ret;

	i = 0;
	args_nb = get_args_nb(token);
	printf("args_nb = %zu\n", args_nb);
	cmd->args = (char **)malloc(sizeof(char *) * (args_nb + 1));
	if (!cmd->args)
		return (1);
	while (token && token->type != '|')
	{
		if (is_rediroperator(token->type))
			ret = set_redirections(sh, cmd, (char *)token->content);
		else
			ret = fill_arg(sh, cmd->args, &i, (char *)token->content);
		if (ret == FAIL)
		{
			clear_tab(cmd->args, i);
			free(cmd);
			return (1);
		}
		token = token->next;
	}
	cmd->args[i] = NULL;
	return (0);
}
