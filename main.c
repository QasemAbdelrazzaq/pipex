#include "pipex.h"

static void	px_init(t_px *px, char **av, char **envp)
{
	px->av = av;
	px->envp = envp;
	px->infile = -1;
	px->outfile = -1;
	px->pipefd[0] = -1;
	px->pipefd[1] = -1;
	px->p1 = -1;
	px->p2 = -1;
}

static int	px_open_files(t_px *px)
{
	int	ret;

	ret = 0;
	px->infile = open(px->av[1], O_RDONLY);
	if (px->infile < 0)
		perror(px->av[1]);
	px->outfile = open(px->av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (px->outfile < 0)
	{
		perror(px->av[4]);
		ret = 1;
	}
	return (ret);
}

static void	px_make_pipe(t_px *px)
{
	if (pipe(px->pipefd) == -1)
	{
		cleanup(&px->infile, &px->outfile, px->pipefd);
		fatal("pipe");
	}
}

static void	px_fork_children(t_px *px)
{
	px->p1 = fork();
	if (px->p1 == -1)
		fatal("fork");
	if (px->p1 == 0)
		child1(px->infile, px->pipefd, px->av[2], px->envp);
	px->p2 = fork();
	if (px->p2 == -1)
		fatal("fork");
	if (px->p2 == 0)
		child2(px->outfile, px->pipefd, px->av[3], px->envp);
}

static void	px_parent_wait(t_px *px)
{
	cleanup(&px->infile, &px->outfile, px->pipefd);
	waitpid(px->p1, NULL, 0);
	waitpid(px->p2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_px	px;
	int		ret;

	ret = 0;
	if (ac != 5)
	{
		write(2, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 48);
		return (1);
	}
	px_init(&px, av, envp);
	ret = px_open_files(&px);
	if (ret != 0)
	{
		cleanup(&px.infile, &px.outfile, px.pipefd);
		return (1);
	}
	px_make_pipe(&px);
	px_fork_children(&px);
	px_parent_wait(&px);
	return (0);
}
