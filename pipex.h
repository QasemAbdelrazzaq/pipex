#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_px
{
	int		pipefd[2];
	int		infile;
	int		outfile;
	pid_t	p1;
	pid_t	p2;
	char	**av;
	char	**envp;
}	t_px;

void	close_safe(int *fd);
void	cleanup(int *infile, int *outfile, int pipefd[2]);
void	fatal(const char *msg);

void	child1(int infile, int pipefd[2], char *cmd, char **envp);
void	child2(int outfile, int pipefd[2], char *cmd, char **envp);
void	exec_cmd(char *cmd, char **envp);

int		is_space(char c);
int		is_all_space(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *a, const char *b, size_t n);
char	*ft_strchr(const char *s, int c);

char	**split_ws(const char *s);
void	free_strv(char **v);

char	*substr_dup(const char *s, int start, int end);
char	*join_path_cmd(const char *dir, const char *cmd);
char	*next_path_dir(char *path, int *i);
char	*get_env_value(char **envp, const char *key);

void	cmd_not_found(const char *cmd);

#endif
