#include <stdio.h>
#include <unistd.h>

void	pipex(int f1, char *cmd1, char *cmd2, int f2)
{
	int	fd[2];
	// fd[0] for read
	// fd[1] for write
	int	id;
	int	pipex_id;

	pipex_id = pipe(fd);
	id = fork();
	if (id < 0)
		return (perror("Fork: "));
	if (!id)
	{
		ft_child_process(f1, cmd1);
		close(fd[0]);
		write(fd[1], "Z", 1);
		close(fd[1]);
	}
	else
	{
		ft_parent_process(f2, cmd2);
		char	c;
		close(fd[1]);
		read(fd[0], &c, 1);
		printf("%c\n", c);
		close(fd[0]);
	}

	return (0);
}

int	main(int narg, char **args)
{
	pipex(ft_atoi(args[0]), args[1], args[2], ft_atoi(args[3]));
}
