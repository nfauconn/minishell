/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:32:33 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/14 15:18:45 by nfauconn         ###   ########.fr       */
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
	while (ret > 0)
	{
		write(cmd->redir[1], buf, ret);
		ret = read(cmd->redir[0], buf, BUFFER_SIZE);
		//ret = read(STDIN_FILENO, buf, BUFFER_SIZE);
	}
	exit(0);
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
		if (access(cmd_args[0], X_OK))
			execve(cmd_args[0], cmd_args, env_tab);
		while (path_tab[i] != NULL)
		{
			path_exec = join_path(path_tab[i], cmd_args[0]);
			if (!path_exec)
				break ;
			if (access(path_exec, X_OK))
				execve(path_exec, cmd_args, env_tab);
			free(path_exec);
			++i;
		}
		if (errno)
			ft_printerror("minish: %s: %s\n", cmd_args[0], strerror(errno));
	}
	else if (cmd_args && !cmd_args[0] && cmd->redir[1] != -42)
	{
		handle_redironly_cmd(cmd);
	}
	clean_string_array(path_tab);
	clean_string_array(env_tab);
}

int	cmd_proc_main_job(t_sh *sh, pid_t pid, t_cmd **cmd, int fd[2])
{
	/*MARCHE MAIS A CHECKER FD NON FERMEE*/
	if (pid)
	{
		if ((*cmd)->redir[0] != STDIN_FILENO)
			close ((*cmd)->redir[0]);
		close (fd[STDOUT_FILENO]);
		(*cmd)->redir[0] = fd[STDIN_FILENO];
		*cmd = (*cmd)->next;
		return (0);
	}
	if ((*cmd)->redir[0] > STDERR_FILENO)
	{
		close(fd[STDIN_FILENO]);
		fd[STDIN_FILENO] = (*cmd)->redir[0];
	}
	if ((*cmd)->redir[1] > STDERR_FILENO)
	{
		close(fd[STDOUT_FILENO]);
		fd[STDOUT_FILENO] = (*cmd)->redir[1];
	}
	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	cmd_run_com(sh, *cmd);
	exit(-1);
}

int	cmd_execute(t_sh *sh)
{
	int		fd[2];
	pid_t	pid;
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	while (cmd)
	{
		if (cmd->next && pipe(fd) < 0)
		{
			perror("minishell");
			return (-1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("minishell");
			return (-1);
		}
		if (cmd_proc_main_job(sh, pid, &cmd, fd))
			return (errno);
	}
	while (waitpid(-1, NULL, 0) >= 0)
		;
	return (0);
}
