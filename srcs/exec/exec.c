#include "minishell.h"

void	exec_cmd(t_sh *sh, t_cmd *cmd)
{
	if (!cmd->name)
		exit(0);// and close?
	if (cmd->built_i > -1)
		handle_builtin(sh, cmd);
	cmd->env = get_env_tab(sh->env);
	if (cmd->name && access(cmd->name, X_OK) != -1)
		execve(cmd->name, cmd->args, cmd->env);
	cmd->env_paths = get_path_tab(sh->env);
	if (!cmd->env_paths || !find_path(cmd, cmd->env_paths))
		error_exit(cmd->name, NOT_FOUND);
	else
	{
		execve(cmd->path, cmd->args, cmd->env);
		error_exit(cmd->name, NOT_EXECUTABLE);
	}
	error_exit(cmd->name, 1);
}
