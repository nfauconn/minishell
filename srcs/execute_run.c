/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdankou <mdankou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:32:33 by mdankou           #+#    #+#             */
/*   Updated: 2022/06/12 20:49:10 by mdankou          ###   ########.fr       */
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
	
	if (cmd_args && path_tab)
	{
		execve(cmd_args[0], cmd_args, env_tab);
		while (path_tab[i] != NULL)
		{
			path_exec = join_path(path_tab[i], cmd_args[0]);
			if (!path_exec)
				break ;
			execve(path_exec, cmd_args, env_tab);
			free(path_exec);
			++i;
		}
	}
	//perror(cmd_args[0]);
	clean_string_array(path_tab);
	ft_printerror("minish: %s: %s\n", cmd_args[0], strerror(errno));
	clean_string_array(env_tab);
}

int	cmd_proc_main_job(t_sh *sh, pid_t pid, t_cmd **cmd, int fd[2])
{
	/*NE MARCHE PAS POUR LES PIPES*/
	if (pid)
	{
		
		if ((*cmd)->redir[0] != STDIN_FILENO)
			close ((*cmd)->redir[0]);
		close (fd[STDOUT_FILENO]);
		(*cmd)->redir[0] = fd[STDIN_FILENO];
		*cmd = (*cmd)->next;
		return (0);
	}
	if ((*cmd)->redir[0] != -1)
	{
		//close(fd[STDIN_FILENO]);
		fd[STDIN_FILENO] = (*cmd)->redir[0];
		dup2(fd[STDIN_FILENO], STDIN_FILENO);
	}
	if ((*cmd)->redir[1] != -1)
	{
		//close(fd[STDOUT_FILENO]);
		fd[STDOUT_FILENO] = (*cmd)->redir[1];
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	}
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