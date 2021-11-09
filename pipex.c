/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/08 15:36:35 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file2(char *filename)
{
	if (access(filename, F_OK) == 0)
		return (open(filename, O_RDWR));
	else
		return (open(filename, O_CREAT | S_IWOTH));
	return (-1);
}

int	open_file(char *filename)
{
	if (access(filename, F_OK) == 0)
		return (open(filename, O_RDONLY));
	else
	{
		write(1, "The file doesn't exist.\n", 24);
		exit(EXIT_FAILURE);
	}
	return (-1);
}

void	pipex(t_data data)
{
	if (pipe(data.pipefd) == -1)
		exit(EXIT_FAILURE);
	data.pid1 = fork();
	if (data.pid1 == -1)
		exit(EXIT_FAILURE);
	if (data.pid1 == 0)
	{
		dup2(data.pipefd[1], STDOUT);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
		execve(data.path1, data.cmd1, NULL);
	}
	data.pid2 = fork();
	if (data.pid2 == -1)
		exit(EXIT_FAILURE);
	if (data.pid2 == 0)
	{
		dup2(data.pipefd[0], STDIN);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
		execve(data.path2, data.cmd2, NULL);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 5)
	{
		write(1, "Invalid number of arguments.\n", 29);
		exit(EXIT_FAILURE);
	}
	data.read_file = open_file(argv[1]);
	data.write_file = open_file2(argv[4]);
	if (data.read_file == -1 || data.write_file == -1)
	{
		write(1, "Can't open this file, sorry.\n", 29);
		exit(EXIT_FAILURE);
	}
	data = path1(argv[2], env);
	data = path2(data, argv[3], env);
	dup2(data.read_file, STDIN);
	dup2(data.write_file, STDOUT);
	pipex(data);
	free(data.path1);
	free(data.path2);
	free_str(data.cmd1);
	free_str(data.cmd2);
	return (0);
}
