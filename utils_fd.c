#include "pipex.h"

void	close_safe(int *fd)
{
	if (!fd)
		return ;
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void	cleanup(int *infile, int *outfile, int pipefd[2])
{
	close_safe(&pipefd[0]);
	close_safe(&pipefd[1]);
	close_safe(infile);
	close_safe(outfile);
}

void	fatal(const char *msg)
{
	perror(msg);
	exit(1);
}
void	cmd_not_found(const char *cmd)
{
	size_t	len;

	write(2, "pipex: command not found: ", 26);
	len = ft_strlen(cmd);
	write(2, cmd, len);
	write(2, "\n", 1);
	exit(127);
}
