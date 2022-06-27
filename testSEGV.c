#include <stdio.h>

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		printf("av[1][%d] = %c\n", i, av[1][i]);
		i++;
	}
	return (0);
}