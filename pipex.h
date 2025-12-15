/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:05:03 by qabdel-r          #+#    #+#             */
/*   Updated: 2025/12/13 19:26:43 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
//fork,pipe ,dup2,execve,access,write ,close
#include <unistd.h>
//malloc,free,exit
#include <stdlib.h>
// open and there flags
#include <fcntl.h>
// waitpid and pid_t
#include <sys/wait.h>
#include <sys/types.h>
// for perror
#include <errno.h>
#include <string.h>
#include <stdio.h>
//functoin to print the error
void fatal(const char *msg);
void    close_safe(int *fd);

void	cleanup(int *infile, int *outfile, int pipefd[2]);
void	child2(int outfile, int pipefd[2], char *cmd, char **envp);
void	child1(int infile, int pipefd[2], char *cmd, char **envp)


void exec_cmd(...);
#endif

