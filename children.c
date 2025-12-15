/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:31:36 by qabdel-r          #+#    #+#             */
/*   Updated: 2025/12/13 15:53:30 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(int infile, int pipefd[2], char *cmd, char **envp)
{
	if (dup2(infile, 0) == -1)
		fatal("dup2 infile -> stdin");
	if (dup2(pipefd[1], 1) == -1)
		fatal("dup2 pipe write -> stdout");

		close_safe(&pipefd[0]);
		close_safe(&pipefd[1]);
		close_safe(&infile);

		exec_cmd(cmd, envp);
		fatal("exec_cmd child1");
}
void	child2(int outfile, int pipefd[2], char *cmd, char **envp)
{

	if (dup2(pipefd[0], 0) == -1)
			fatal("dup2 pipe read -> stdin");
		if (dup2(outfile, 1) == -1)
			fatal("dup2 outfile -> stdout");

		close_safe(&pipefd[0]);
		close_safe(&pipefd[1]);
		close_safe(&outfile);

		exec_cmd(cmd, envp);
		fatal("exec_cmd child2");
}
