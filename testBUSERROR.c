#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int	main()
{
	int		fd;
	int		*map;
	int		size = sizeof(int);
	char	*name = "/a";

	shm_unlink(name);
	fd = shm_open(name, O_RDWR | O_CREAT, (mode_t)0600);
	/* ftruncate(fd, size);
	THIS is the cause of the problem --> ftruncate forgotten */
	map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	/* this is what generates the SIGBUS */
	*map = 0;
	return (0);
}
