/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaguiler <aaguiler@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:14:49 by aaguiler          #+#    #+#             */
/*   Updated: 2022/05/25 18:22:41 by aaguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_check_fd(int fd)
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
	char	*path;
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
