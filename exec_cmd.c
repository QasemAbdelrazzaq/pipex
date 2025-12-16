#include "pipex.h"

/*
first this functioio if error huppend this funcito run to print
the error
now if the errno  equal the ENOENT whihc mean there is not such file
and if the ENOIDIR something in the path isn't a directory
free the argv and then exit with the exit code
*/
static void	exit_exec_errno(char *name, char **argv)
{
	int	code;

	perror(name);
	code = 126;
	if (errno == ENOENT || errno == ENOTDIR)
		code = 127;
	free_strv(argv);
	exit(code);
}
/*
make the funciton if there a / in the path
and if the execve fail we go to the exit exit_exec_errno
*/
static void	exec_direct(char **argv, char **envp)
{
	execve(argv[0], argv, envp);
	exit_exec_errno(argv[0], argv);
}
/*
the main goal is to try every path in the PATH
and the access is mean to see if we have the permission to
 do run this path on the full
 and the X_OK mean the type of test is the execute permission
 and the access return teh -1 if the file not found or i don't have
 the permsion  or the path have problem
 and put the reson on th errno

*/
static void	try_one_full(char *full, char **argv, char **envp)
{
	if (access(full, X_OK) == 0)
	{
		execve(full, argv, envp);
		perror(full);
		free(full);
		free_strv(argv);
		exit(126);
	}
}
/*
the main goal to search in the file of path
the next path dir have the next dir in the PATH  join path cmd join the cmd with the path that we take it form upove funcoitn
try this path adn see if it work or not
*/
static void	search_in_path(char *path, char **argv, char **envp)
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
		try_one_full(full, argv, envp);
		free(full);
	}
}
/*
this function like the main put for execve */
void	exec_cmd(char *cmd, char **envp)
{
	char	**argv;
	char	*path;

	if (is_all_space(cmd))
		cmd_not_found("");
	argv = split_ws(cmd);
	if (!argv || !argv[0])
	{
		free_strv(argv);
		cmd_not_found(cmd);
	}
	if (ft_strchr(argv[0], '/'))
		exec_direct(argv, envp);
	path = get_env_value(envp, "PATH");
	if (!path)
	{
		free_strv(argv);
		cmd_not_found(argv[0]);
	}
	search_in_path(path, argv, envp);
	free_strv(argv);
	cmd_not_found(cmd);
}
