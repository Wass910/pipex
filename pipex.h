/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:27 by idhiba            #+#    #+#             */
/*   Updated: 2021/11/08 12:52:28 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1

typedef struct s_data{
	char	**cmd1;
	char	*path1;
	char	**cmd2;
	char	*path2;
	int		read_file;
	int		write_file;
	int		pid1;
	int		pid2;
	int		pipefd[2];
}				t_data;

char	**ft_split(char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dest, char *src);
t_data	path2(t_data data, char *command, char **env);
t_data	path1(char *command, char **env);
void	free_str(char **str);
#endif
