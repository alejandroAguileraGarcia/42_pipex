#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	fd[2];
	// fd[0] for read
	// fd[1] for write
	int	id;
	int	pid;

	pid = pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], "Z", 1);
		close(fd[1]);
	}
	else
	{
		char	c;
		close(fd[1]);
		read(fd[0], &c, 1);
		printf("%c\n", c);
		close(fd[0]);
	}

	return (0);
}
