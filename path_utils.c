#include "pipex.h"

char	*substr_dup(const char *s, int start, int end)
{
	int		len;
	char	*out;
	int		i;

	len = end - start;
	out = (char *)malloc((size_t)len + 1);
	i = 0;
	if (!out)
		return (NULL);
	while (start + i < end)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*join_path_cmd(const char *dir, const char *cmd)
{
	char	*out;
	size_t	i;
	size_t	j;
	size_t	a;
	size_t	b;

	a = ft_strlen(dir);
	b = ft_strlen(cmd);
	out = (char *)malloc(a + b + 2);
	if (!out)
		return (NULL);
	i = 0;
	while (i < a)
	{
		out[i] = dir[i];
		i++;
	}
	out[i] = '/';
	i = i + 1;
	j = 0;
	while (j < b)
		out[i++] = cmd[j++];
	out[i] = '\0';
	return (out);
}

char	*next_path_dir(char *path, int *i)
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

char	*get_env_value(char **envp, const char *key)
{
	size_t	klen;
	int		i;
	char	*val;

	klen = ft_strlen(key);
	i = 0;
	val = NULL;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], key, klen) == 0 && envp[i][klen] == '=')
		{
			val = (char *)envp[i];
			val = val + klen + 1;
			return (val);
		}
		i++;
	}
	return (NULL);
}
