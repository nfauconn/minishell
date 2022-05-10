#include"minishell.h"

char	*get_input()
{
	char	*line_read;

	line_read = readline("minishell> ");
	if (line_read && *line_read)
	{
		if (ft_strncmp(line_read, "exit", 4) == 0)
		{
			free(line_read);
			exit(1);
		}
		add_history(line_read);
	}
	else if (line_read && *line_read == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		free(line_read);
		exit(1);
	}
	return (line_read);
}

int	main()
{
	t_input	input;

	while (1)
	{
		get_signals();
		input.line_read = get_input();
		input.args = tokenized_cmd(&input, input.line_read);
		int i = 0;
		while (input.args[i])
			printf("|%s| ", input.args[i++]);
		if (i > 0)
			printf("\n");
		end(&input);
	}
}