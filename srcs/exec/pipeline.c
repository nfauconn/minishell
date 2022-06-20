/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:32:33 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/20 13:15:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int8_t	last_status = 0;

void redironly_cmd(t_cmd *cmd)
{
	ssize_t	ret;
	char	buf[BUFFER_SIZE];

	//ret = read(STDIN_FILENO, buf, BUFFER_SIZE);
	ret = read(cmd->redir_in, buf, BUFFER_SIZE);
	if (ret < 0)
		exit(exec_error("read: ", strerror(errno)));
	while (ret > 0)
	{
		write(cmd->redir_out, buf, ret);
		ret = read(cmd->redir_in, buf, BUFFER_SIZE);
		if (ret < 0)
			exit(exec_error("read: ", strerror(errno)));
		//ret = read(STDIN_FILENO, buf, BUFFER_SIZE);
	}
}

static void	exec_cmd(t_sh *sh, t_cmd *cmd)
{
	char	**paths;
	char	**env_tab;

	env_tab = get_env_tab(sh->env);
	paths = get_path_tab(sh->env);
	if (cmd->name && paths)
	{
		if (access(cmd->name, X_OK) != -1)
			execve(cmd->name, cmd->args, env_tab);
		else if (find_path(cmd, paths))
		{
			execve(cmd->path, cmd->args, env_tab);
			last_status = NOT_EXECUTABLE;
			error_display("permission denied", cmd->name);
		}
		else
		{
			last_status = NOT_FOUND;
			error_display(cmd->name, "command not found");
		}
	}
	else if (cmd->args && !cmd->name && cmd->redir_out != FILE_NOT_USED)
		redironly_cmd(cmd);
	ft_str_array_free(paths);
	ft_str_array_free(env_tab);
	exit(last_status);
}

void	child_seq(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	close(p[0]);
	if (cmd->redir_in > STDIN_FILENO)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	else if (fd_in)
		dup2_close_old(fd_in, STDIN_FILENO);
	if (cmd->redir_out > STDOUT_FILENO)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(p[1], STDOUT_FILENO);
	close(p[1]);
	exec_cmd(sh, cmd);
}

void	parent_seq(int p[2], int *fd)
{
	close(p[1]);
	close_if_exists(*fd);
	*fd = p[0];
}

int	cmd_execute(t_sh *sh)
{
	int		p[2];
	int		fd_in;
	pid_t	pid;
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	fd_in = 0;
	signal_catching_mode(PGM_EXEC);
	while (cmd)
	{
		if (pipe(p) < 0)
			return (exec_error("pipe: ", strerror(errno)));
		pid = fork();
		if (pid < 0)
			return (exec_error("fork: ", strerror(errno)));
		if (pid == 0)
			child_seq(sh, cmd, p, fd_in);
		else
			parent_seq(p, &fd_in);
		cmd = cmd->next;
	}
	wait_children(sh);
	signal_catching_mode(INTERACTIVE);
	return (last_status);
}
