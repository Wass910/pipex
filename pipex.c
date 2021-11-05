#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "pipex.h"

char    *get_path(char *cmd, char **env)
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
    if (access(filename, F_OK) == 1)
    { 
    return (open(filename, O_RDONLY));
    }
    else
    return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
    return (-1);
}

int main(int argc, char **argv, char **env)
{
    int pipefd[2];
    char    *cmd[] = {"cat", "pipex.h", NULL};
    char *buf;
    char *path;

    int new_file  = open_file(argv[1]) ;
    dup2(new_file, 1);
    path = get_path(argv[2], env);
    execve(path, cmd, env);
    printf("path = %s\n", path);
    // if (pipe(pipefd) == -1) {
    //      perror("pipe");
    //      exit(EXIT_FAILURE);
    // }
    // int pid1 = fork();
    // if (pid1 < 0)
    //     return 1;
    // if (pid1 == 0)
    // {
    //     dup2(pipefd[1], STDOUT);
    //     close(pipefd[0]);
    //     close(pipefd[1]);
    //     execve("", , "google", NULL);
    // }
    // int pid2 = fork();
    // if (pid2 < 0)
    //     return 1;
    // int new_file  = open_file(argv[1]) ;
    // if (pid2 == 0)
    // {
    //     dup2(newfile, STDIN);
    //     close(pipefd[0]);
    //     close(pipefd[1]);
    //     execve("grep", "grep", "rtt", NULL);
    // }
    // close(pipefd[0]);
    // close(pipefd[1]);
    // waitpid(pid1, NULL,0);
    // waitpid(pid2, NULL, 0);
    // int new_file  = open_file(argv[1]) ;
    // dup2(new_file, 1);
    // printf("env de i = %d\n", new_file);
    // int i = 0;
    //while (strncmp(env[i], "PATH=", 5) != 0)
    //{
    //    i++;
    //}
    //printf("env de i = %s\n", env[i]);
    // if ((new_file = open_file(argv[1])) == -1)
    // {
    //     printf("Error on the file.\n");
    //     exit(EXIT_FAILURE);
    // }
    // if (pipe(pipefd) == -1) {
    //     perror("pipe");
    //     exit(EXIT_FAILURE);
    // }

    // cpid = fork();
    // if (cpid == -1) {
    //     perror("fork");
    //     exit(EXIT_FAILURE);
    // }

    // if (cpid == 0) {    /* Le fils lit dans le tube */
    //     close(pipefd[1]);  /* Ferme l'extrémité d'écriture inutilisée */
    //     while (read(pipefd[0], &buf, 1) > 0)
    //         write(1, &buf, 1);
    //     write(1, "\n", 1);
    //     close(pipefd[0]);
    //     _exit(EXIT_SUCCESS);

    // } else {                    /* Le père écrit argv[1] dans le tube */
    //     close(pipefd[0]);       /* Ferme l'extrémité de lecture inutilisée */
    //     write(pipefd[1], argv[2], strlen(argv[2]));
    //     dup2(pipefd[0], new_file);
    //     close(pipefd[1]);       /* Le lecteur verra EOF */
    //     wait(NULL);             /* Attente du fils */
    //     exit(EXIT_SUCCESS);
    // }
    return 0;
}
