/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/30 02:39:04 by itopchu       #+#    #+#                 */
/*   Updated: 2022/12/30 02:39:04 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**args;

	i = 0;
	args = ft_split(cmd, ' ');
	if (!args)
		error_exit("Malloc failed", EXIT_FAILURE);
	path = find_path(args[0], envp);
	if (!path)
		error_exit("Path not found", EXIT_FAILURE);
	if (execve(path, args, envp) == -1)
		error_exit("Command not found", EXIT_FAILURE);
}

void	exec_child(char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error_exit("pipe failed", EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		error_exit("fork failed", EXIT_FAILURE);
	else if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			error_exit("dup2 WRITE failed", EXIT_FAILURE);
		exec_cmd(cmd, envp);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			error_exit("dup2 READ failed", EXIT_FAILURE);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	in;
	int	out;

	i = 2;
	if (ac < 5)
		error_exit("Invalid use!\n ./pipex <in> <cmdN> <cmdN> <out>",
			EXIT_FAILURE);
	in = ft_openfile(av[1], "in");
	out = ft_openfile(av[ac - 1], "out");
	if (dup2(in, STDIN_FILENO) < 0)
		error_exit("dup2 for in failed", EXIT_FAILURE);
	if (dup2(out, STDOUT_FILENO) < 0)
		error_exit("dup2 for out failed", EXIT_FAILURE);
	while (i < ac - 2)
	{
		exec_child(av[i], envp);
		i++;
	}
	exec_cmd(av[i], envp);
	close(in);
	close(out);
	exit(EXIT_SUCCESS);
}
