/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaguiler <aaguiler@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:14:16 by aaguiler          #+#    #+#             */
/*   Updated: 2022/05/25 18:31:42 by aaguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Cambiar open por access en ft_get_path

#include "pipex.h"

void	child_process(int *fd, char **argv, char **envp)
{
	int		fd_file;
	char	*path;
	char	**args_execve;

	close(fd[0]);
	fd_file = open(argv[1], O_RDONLY);
	ft_check_fd(fd_file);
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	args_execve = ft_split(argv[2], ' ');
	path = ft_get_path(args_execve[0], envp);
	if (execve(path, args_execve, envp) == -1)
	{
		perror("Pipex: command not found");
		ft_free_paths(args_execve);
		free(path);
		exit(0);
	}
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int		fd_file;
	char	*path;
	char	**args_execve;

	close(fd[1]);
	fd_file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	ft_check_fd(fd_file);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
	args_execve = ft_split(argv[3], ' ');
	path = ft_get_path(args_execve[0], envp);
	if (execve(path, args_execve, envp) == -1)
	{
		perror("Pipex: command not found");
		ft_free_paths(args_execve);
		free(path);
		exit(0);
	}
}

void	pipex(char **argv, char **envp)
{
	int	pid;
	int	fd[2];

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
		perror("Pipex: invalid args");
		return (0);
	}
	pipex(args, envp);
	return (0);
}
