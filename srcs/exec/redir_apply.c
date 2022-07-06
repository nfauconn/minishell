#include "minishell.h"

void	redir_apply(t_cmd *cmd, int p[2], int fd_in)
{
	close(p[0]);
	if (cmd->redir_in == REDIR_FAIL || cmd->redir_out == REDIR_FAIL)
	{
		close(p[1]);
		exit(WRONG_REDIR);
	}
	if (cmd->redir_in > NO_REDIR)
		dup2_close_old(cmd->redir_in, STDIN_FILENO);
	else if (fd_in)
		dup2_close_old(fd_in, STDIN_FILENO);
	if (cmd->redir_out > NO_REDIR)
		dup2_close_old(cmd->redir_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(p[1], STDOUT_FILENO);
	close(p[1]);
}
