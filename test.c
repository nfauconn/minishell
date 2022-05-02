#include"minishell.h"

void	clean_exit(int sig_num, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)sig_num;
	exit(1);
}

void	new_prompt(int sig_num, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig_num == SIGINT)
		printf("%s\n", readline("minishell> "));
}

int	main()
{
	struct sigaction	s_act;

	s_act.sa_sigaction = new_prompt;
	sigaction(SIGINT, &s_act, NULL);
	printf("%s\n", readline("minishell> "));
}