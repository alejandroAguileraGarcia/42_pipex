#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Cambiar open por access en ft_get_path
//Eliminar printf
//Definir split
//Definir ft_strncmp
//Definir ft_strchr
//Definir ft_strjoin

void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	ft_check_fd(int fd, char *file_name)
{
	if (fd == -1)
		perror("Pipex: no such file or directory");
}

char	**ft_get_all_paths(char **envp)
{
	int		i;
	char	*path_wout_path;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path_wout_path = ft_strchr(envp[i], '/');
	paths = ft_split(path_wout_path, ':');
	return (paths);
}

char	*ft_get_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	path;
	int		i;
	int		fd;

	all_paths = ft_get_all_paths(envp);
	i = 0;
	while (all_paths[i])
	{
		path = ft_strjoin(ft_strjoin(all_paths[i], "/"), cmd);
		fd = open(path, O_RDONLY);
		if (fd >= 0)
		{
			ft_free_paths(all_paths);
			close(fd);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_paths(all_paths);
	return (NULL);
}

void	child_process(int *fd, char **argv, char **envp)
{
	int		fd_file;
	char	*path;
	char	**args_execve;

	close(fd[0]);
	fd_file = open (argv[1], O_RDONLY);
	ft_check_fd(fd_file, argv[1]);
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	args_execve = ft_split(argv[2], ' ');
	path = ft_get_path(arg_execve[0], envp);
	if (execve(path, args_execve, envp) == -1)
	{
		perror("Pipex: command not found");
		ft_free_paths(args_execve);
		free(path);
		exit(0);
	}
}

void	ft_parent_process(int *fd, char **argv, char **envp)
{
	int		fd_file;
	char	*path;
	char	**args_execve;

	close(fd[1]);
	fd_file = open (argv[4], O_RDONLY);
	ft_check_fd(fd_file, argv[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
	args_execve = ft_split(argv[3], ' ');
	path = ft_get_path(arg_execve[0], envp);
	if (execve(path, args_execve, envp) == -1)
	{
		perror("Pipex: command not found");
		ft_free_paths(args_execve);
		free(path);
		exit(0);
	}
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
