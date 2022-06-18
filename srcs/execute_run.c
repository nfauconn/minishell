/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:32:33 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/18 17:04:54 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_string_array(char **array);
char	*join_path(char const *penv, char const *pexec);

char	**get_env_tab(t_list *env)
{
	size_t	len;
	char	**tab;

	len = ft_lstsize(env);
	tab = (char**)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	len = 0;
	while (env)
	{
		tab[len++] = ft_strdup(env->content);
		if (!tab[len])
			break ;
		env = env->next;
	}
	if (env)
	{
		while (--len >= 0)
			free(tab[len]);
		free(tab);
		return (NULL);
	}
	tab[len] = NULL;
	return (tab);
}

char	**get_path_tab(t_list *env)
{
	char	**tab;
	while (env && ft_strncmp(env->content, "PATH=", 5))
		env = env->next;
	if (!env)
	{
		tab = (char **)malloc(sizeof(char *));
		if (!tab)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	return (ft_split(env->content + 5, ':'));
}

void handle_redironly_cmd(t_cmd *cmd)
{
	ssize_t	ret;
	char	buf[BUFFER_SIZE];

	//ret = read(STDIN_FILENO, buf, BUFFER_SIZE);
	ret = read(cmd->redir[0], buf, BUFFER_SIZE);
	if (ret < 0)
		exit(exec_error("read: ", strerror(errno)));
	while (ret > 0)
	{
		write(cmd->redir[1], buf, ret);
		ret = read(cmd->redir[0], buf, BUFFER_SIZE);
		if (ret < 0)
			exit(exec_error("read: ", strerror(errno)));
		//ret = read(STDIN_FILENO, buf, BUFFER_SIZE);
	}
}

void	cmd_run_com(t_sh *sh, t_cmd *cmd)
{
	int		i;
	char	**cmd_args;
	char	**path_tab;
	char	**env_tab;
	char	*path_exec;

	i = 0;
	env_tab = get_env_tab(sh->env);
	path_tab = get_path_tab(sh->env);
	cmd_args = cmd->cmd_tab;
	if (cmd_args && cmd_args[0] && path_tab)
	{
		if (access(cmd_args[0], X_OK) != -1)
			execve(cmd_args[0], cmd_args, env_tab);
		while (path_tab[i] != NULL)
		{
			path_exec = join_path(path_tab[i], cmd_args[0]);
			if (!path_exec)
				break ;
			if (access(path_exec, X_OK) != -1)
				execve(path_exec, cmd_args, env_tab);
			free(path_exec);
			++i;
		}
		ft_printerror("%s: %s\n", cmd_args[0], "command not found");
	}
	else if (cmd_args && !cmd_args[0] && cmd->redir[1] != FILE_NOT_USED)
	{
		handle_redironly_cmd(cmd);
	}
	clean_string_array(path_tab);
	clean_string_array(env_tab);
}

int	child_proc_job(t_sh *sh, t_cmd *cmd, int p[2], int fd_in)
{
	close(p[0]);
	if (cmd->redir[0] > STDIN_FILENO)
		dup2_close_old(cmd->redir[0], STDIN_FILENO);
	else if (fd_in != STDIN_FILENO)
		dup2_close_old(fd_in, STDIN_FILENO);
	if (cmd->redir[1] > STDOUT_FILENO)
		dup2_close_old(cmd->redir[1], STDOUT_FILENO);
	else if (cmd->index != sh->cmd_nb - 1)
		dup2_close_old(p[1], STDOUT_FILENO);
	cmd_run_com(sh, cmd);
	exit(127);
//	exit(exec_error("NLABLAk: ", strerror(errno)));
}

int	parent_proc_job(int p[2], int *fd_in)
{
/*  	if (p[1] > STDERR_FILENO && close(p[1]) == -1)
		return (exec_error("close: ", strerror(errno)));  */
	close(p[1]);
	*fd_in = p[0];
	return (0);
}

int	cmd_execute(t_sh *sh)
{
	int		p[2];
	int		fd_in;
	pid_t	pid;
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	fd_in = 0;
	while (cmd)
	{
		if (cmd->next && pipe(p) < 0)
			return (exec_error("pipe: ", strerror(errno)));
		pid = fork();
		if (pid < 0)
			return (exec_error("fork: ", strerror(errno)));
		if (pid == 0)
			child_proc_job(sh, cmd, p, fd_in);
		else
			parent_proc_job(p, &fd_in);
		cmd = cmd->next;
	}
	int status = 0;
	size_t	i = 0;
	while (i < sh->cmd_nb -1 )
	{
		pid = waitpid(-1, &status, WUNTRACED);
		if (WIFEXITED(status) && status == 139)
			ft_printerror("segfault\n");
		i++;
	}
	return (SUCCESS);
}

/*		if (cmd->next && pipe(fd) < 0)
			return(exec_error("pipe: ", strerror(errno)));
		pid = fork();
		if (pid < 0)
			
		if (cmd_proc_main_job(sh, pid, &cmd, fd) == -1)
			return (errno);*/
