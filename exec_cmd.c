/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:32:05 by qabdel-r          #+#    #+#             */
/*   Updated: 2025/12/14 14:19:46 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
126 like the shell mean that the permission denied is a directory
errno is the varibal that system put the reson of the the error
ENOENT NO SUCH File or Directory
ENOTDIR NOT a directory
if the reson of the error on of the upov put it 127

*/
static void	exec_direct(char **argv, char **envp)
{
	int	code;

	execve(argv[0], argv, envp);

	perror(argv[0]);

	code = 126;
	if (errno == ENOENT || errno == ENOTDIR)
		code = 127;

	free_strv(argv);
	exit(code);
}
static char	*next_path_dir(char *path, int *i)
{
	int		start;
	int		end;
	char	*dir;

	start = *i;
	while (path[*i] && path[*i] != ':')
		*i = *i + 1;
	end = *i;
	if (path[*i] == ':')
		*i = *i + 1;
	dir = substr_dup(path, start, end);
	return (dir);
}
 void	try_path_exec(char *path, char **argv, char **envp)
{
	int		i;
	char	*dir;
	char	*full;

	i = 0;
	while (path[i])
	{
		dir = next_path_dir(path, &i);
		if (!dir)
			fatal("malloc");

		full = join_path_cmd(dir, argv[0]);
		free(dir);
		if (!full)
			fatal("malloc");

		if (access(full, X_OK) == 0)
		{
			execve(full, argv, envp);
			perror(full);
			free(full);
			free_strv(argv);
			exit(126);
		}
		free(full);
	}
}
