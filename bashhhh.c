
#include "includes/extern_libs.h"

int	main(int ac, char **av, char **env)
{
	if (ac == 2)
	{
		execve("bash\n", "bash", env);
	}
}