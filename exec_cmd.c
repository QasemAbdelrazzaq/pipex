#include "pipex.h"

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

static void	exec_direct(char **argv, char **envp)
{
	execve(argv[0], argv, envp);
	exit_exec_errno(argv[0], argv);
}

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
