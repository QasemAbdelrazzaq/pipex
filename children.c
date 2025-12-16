#include "pipex.h"

static void	child1_no_infile(int pipefd[2])
{
	close_safe(&pipefd[0]);
	close_safe(&pipefd[1]);
	exit(1);
}

void	child1(int infile, int pipefd[2], char *cmd, char **envp)
{
	if (infile < 0)
		child1_no_infile(pipefd);
	if (dup2(infile, 0) == -1)
		fatal("dup2 infile");
	if (dup2(pipefd[1], 1) == -1)
		fatal("dup2 pipe write");
	close_safe(&pipefd[0]);
	close_safe(&pipefd[1]);
	close_safe(&infile);
	exec_cmd(cmd, envp);
	fatal("exec_cmd child1");
}

void	child2(int outfile, int pipefd[2], char *cmd, char **envp)
{
	if (dup2(pipefd[0], 0) == -1)
		fatal("dup2 pipe read");
	if (dup2(outfile, 1) == -1)
		fatal("dup2 outfile");
	close_safe(&pipefd[0]);
	close_safe(&pipefd[1]);
	close_safe(&outfile);
	exec_cmd(cmd, envp);
	fatal("exec_cmd child2");
}
