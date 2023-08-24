/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/31 04:46:42 by itopchu       #+#    #+#                 */
/*   Updated: 2022/12/31 04:46:42 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*Depending on status it will open the document as input or output.*/
int	ft_openfile(char *path, char *status)
{
	int	fd;

	fd = -1;
	if (ft_strncmp(status, "out", 3) == 0)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else
		fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Open file fail", EXIT_FAILURE);
	return (fd);
}

char	*find_full_path(char *cmd, char **dirs)
{
	char	*full_path;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = -1;
	while (dirs[++i])
	{
		full_path = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, F_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
	}
	return (full_path);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;

	i = -1;
	path = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i];
			break ;
		}
	}
	if (!path)
		return (NULL);
	paths = ft_split(path + 5, ':');
	full_path = find_full_path(cmd, paths);
	free_vector(paths);
	return (full_path);
}

/*Prints the error than exits the program by cleaning 
up and releasing any resources that program was using.*/
void	error_exit(const char *error, int exit_code)
{
	write(STDERR_FILENO, "Pipex error: ", 13);
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
	exit(exit_code);
}

void	free_vector(char **obj)
{
	int	i;

	i = 0;
	while (obj[i])
		free(obj[i++]);
	free(obj);
}
