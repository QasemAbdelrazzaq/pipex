/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:12:39 by qabdel-r          #+#    #+#             */
/*   Updated: 2025/12/14 14:51:50 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
pipefd[1]for write
pipefd[0]for reading
ifilde and outfile for filedescriptor
and p1 and p2 to save the PID for the child

fatal is to print the error and open file
o_creat to make file if does not and O_trunc clear the under file if does not apear
0644 give apermitoin

envp is the environment pointer
and if i want to now where is the command i write which and the comman
and command -v ls

and if i give permation  over the syste umask give more
*/
int main(int ac, char **av, char **envp)
{
    int     pipefd[2];
    int     infile;
    int     outfile;
    pid_t   p1;
    pid_t   p2;

    infile = -1;
    outfile = -1;
    pipefd[0] = -1;
    pipefd[1] = -1;

    if (ac != 5)
    {
        write(2, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 48);
        return (1);
    }

    infile = open(av[1], O_RDONLY);
    if (infile < 0)
    {
        cleanup(&infile, &outfile, pipefd);
        fatal("open infile");
    }

    outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfile < 0)
    {
        cleanup(&infile, &outfile, pipefd);
        fatal("open outfile");
    }

    if (pipe(pipefd) == -1)
    {
        cleanup(&infile, &outfile, pipefd);
        fatal("pipe");
    }

    p1 = fork();
    if (p1 == -1)
    {
        cleanup(&infile, &outfile, pipefd);
        fatal("fork");
    }
    if (p1 == 0)
        child1(infile, pipefd, av[2], envp);

    p2 = fork();
    if (p2 == -1)
    {
        cleanup(&infile, &outfile, pipefd);
        fatal("fork");
    }
    if (p2 == 0)
        child2(outfile, pipefd, av[3], envp);

    cleanup(&infile, &outfile, pipefd);

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    return (0);
}
c

