#include "pipex.h"

void	free_str(char **str)
{
	int	line;

	line = 0;
	while (str[line])
	{
		free(str[line]);
		line++;
	}
	free(str);
}

char	*get_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path = env[i] + 5;
	return (path);
}

int	what_path(char **path, char *cmd)
{
	int	i;
	char	*str;

	i = 0;
	while (path[i])
	{
		str = ft_strcat(path[i], cmd);
		if (access(str, F_OK) == 0)
		{
			free(str);
			return (i);
		}
		free(str);
		i++;
	}
	return (-1);
}

t_data	path1(t_data data, char *command, char **env)
{
	char	*path;
	char	**good_path;
	int		i;

	data.cmd1 = ft_split(command, ' ');
	path = get_path(env);
	good_path = ft_split(path, ':');
	i = what_path(good_path, data.cmd1[0]);
	data.path1 = ft_strcat(good_path[i], data.cmd1[0]);
	free_str(good_path);
	return (data);
}

t_data	path2(t_data data, char *command, char **env)
{
	char	*path;
	char	**good_path;
	int		i;

	data.cmd2 = ft_split(command, ' ');
	path = get_path(env);
	good_path = ft_split(path, ':');
	i = what_path(good_path, data.cmd2[0]);
	data.path2 = ft_strcat(good_path[i], data.cmd2[0]);
	free_str(good_path);
	return (data);
}
