#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "pipex.h"

char    *get_path(char **env)
{
    char *path;
    int i = 0;

    while (strncmp(env[i], "PATH=", 5) != 0)
    {
       i++;
    }
    path = env[i] + 5;
    return path;
}

int open_file(char *filename)
{
    if (access(filename, F_OK) == 0)
        return (open(filename, O_RDWR));
    else
        return (open(filename, O_CREAT | S_IWOTH));
    return (-1);
}

int what_path(char **path, char *cmd)
{
    int i = 0;

    while (path[i])
    {
        if (access(ft_strcat(path[i], cmd), F_OK) == 0)
            return (i);
        i++;
    }
    return (-1);
}

t_data    path1(t_data data, char *command, char **env)
{
    char *path;
    char **good_path;
    int i;
    data.cmd1 = ft_split(command, ' ');
    path = get_path(env);
    good_path = ft_split(path, ':');
    i = what_path(good_path, data.cmd1[0]);
    data.path1 = ft_strcat(good_path[i], data.cmd1[0]);
    return (data);
}

t_data    path2(t_data data, char *command, char **env)
{
    char *path;
    char **good_path;
    int i;
    data.cmd2 = ft_split(command, ' ');
    path = get_path(env);
    good_path = ft_split(path, ':');
    i = what_path(good_path, data.cmd2[0]);
    data.path2 = ft_strcat(good_path[i], data.cmd2[0]);
    return (data);
}

void    pipex(t_data data)
{
    int pipefd[2];
    int pid1;
    int pid2;
    if (pipe(pipefd) == -1)
    {
        exit(EXIT_FAILURE);
    }
    pid1 = fork();
    if (pid1 == -1)
        exit(EXIT_FAILURE);
    if (pid1 == 0)
    {
        dup2(pipefd[1], STDOUT);
        close(pipefd[0]);
        close(pipefd[1]);
        execve(data.path1, data.cmd1, NULL);
    }

    pid2 = fork();
    if (pid2 == -1)
        exit(EXIT_FAILURE);
    if (pid2 == 0)
    {
        dup2(pipefd[0], STDIN);
        close(pipefd[0]);
        close(pipefd[1]);
        execve(data.path2, data.cmd2, NULL);
    }
}
int main(int argc, char **argv, char **env)
{
    int pipefd[2];
    int pid1;
    int pid2;
    t_data data;
    int newfile_R;
    int newfile_W;

    data = path1(data, argv[2], env);
    data = path2(data, argv[3], env);
    data.read_file =  open_file(argv[1]);
    data.write_file =  open_file(argv[4]);
    dup2(data.read_file, STDIN);
    dup2(data.write_file, STDOUT);
    pipex(data);
    return 0;
}
