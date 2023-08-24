/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: itopchu <itopchu@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/30 02:39:55 by itopchu       #+#    #+#                 */
/*   Updated: 2022/12/30 02:39:55 by itopchu       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/*==================================*/
/*				MAIN				*/
/*==================================*/
int		main(int ac, char **av, char **envp);
void	exec_child(char *cmd, char **envp);
void	exec_cmd(char *cmd, char **envp);

/*==================================*/
/*				UTILS				*/
/*==================================*/
int		ft_openfile(char *path, char *status);
char	*find_full_path(char *cmd, char **dirs);
char	*find_path(char *cmd, char **envp);
void	error_exit(const char *error, int exit_code);
void	free_vector(char **obj);

#endif