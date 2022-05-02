#include"minishell.h"

void	new_prompt(int sig_num, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig_num == SIGINT)
	{
		printf("\n");
		readline("minishell> ");
	}
/* 	if (sig_num == SIGQUIT)
		rl_clear_history(); */
}

void	set_signals(void)
{
	struct sigaction	s_act;

	s_act.sa_sigaction = new_prompt;
	s_act.sa_flags = SA_SIGINFO;
	sigemptyset(&s_act.sa_mask);
	sigaction(SIGINT, &s_act, NULL);
	sigaction(SIGQUIT, &s_act, NULL);	
}

static char	*line_read = (char *)NULL;

void	get_input()
{
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("minishell> ");
	if (line_read && *line_read)
		add_history(line_read);
//	return (line_read);
}

int	main()
{
//	char *input;

	while (1)
	{
		set_signals();
		get_input();
	}
}