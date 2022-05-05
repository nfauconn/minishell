#include"minishell.h"

char	*get_input()
{
	char	*line_read;

	line_read = readline("minishell> ");
	if (line_read && *line_read)
		add_history(line_read);
	if (line_read && *line_read == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else// if (line_read != // if ((int)line_read == EOF)
	{
		ft_putstr_fd("exit\n", 1);
		free(line_read);
		exit(1);
	}
	return (line_read);
}

int	main()
{
	char	*input;

	while (1)
	{
		get_signals();
		input = get_input();
		free(input);
	}
}