#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Eliminar printf

void	child_process(int f1, char *cmd1, int *fd)
{
	close(fd[0]);
	write(fd[1], "Z", 1);
	close(fd[1]);
}

void	ft_parent_process(int f2, char *cmd1, int *fd)
{
	char	c;

	close(fd[1]);
	read(fd[0], &c, 1);
	printf("%c\n", c);
	close(fd[0]);
}

void	pipex(char **args, char **envp)
{
	int	pid;
	int	fd[2];
	// fd[0] for read
	// fd[1] for write

	pipe(fd);
	pid = fork();
	if (pid < 0)
		perror("Fork: ");
	else if (!pid)
		child_process(fd, argv, envp);
	else
	{
		pid = fork();
		if (pid < 0)
			perror("Fork: ");
		else if (!pid)
			parent_process(fd, argv, envp);
		else
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
	waitpid(pid, NULL, 0);
}

int	main(int narg, char **args, char **envp)
{
	if (narg != 5)
	{
		printf("Invalid args");
		return ;
	}
	pipex(args, envp);
	return (0);
}
