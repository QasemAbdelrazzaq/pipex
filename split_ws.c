#include "pipex.h"

static int	count_words_ws(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_space(s[i]))
			i++;
	}
	return (count);
}

static int	fill_split(char **out, const char *s, int words)
{
	int	i;
	int	w;
	int	start;

	i = 0;
	w = 0;
	while (w < words)
	{
		while (s[i] && is_space(s[i]))
			i++;
		start = i;
		while (s[i] && !is_space(s[i]))
			i++;
		out[w] = substr_dup(s, start, i);
		if (!out[w])
		{
			out[w] = NULL;
			free_strv(out);
			return (-1);
		}
		w++;
	}
	out[w] = NULL;
	return (0);
}

char	**split_ws(const char *s)
{
	char	**out;
	int		words;
	int		ok;

	if (!s)
		return (NULL);
	words = count_words_ws(s);
	out = (char **)malloc(sizeof(char *) * (words + 1));
	if (!out)
		return (NULL);
	ok = fill_split(out, s, words);
	if (ok == -1)
		return (NULL);
	return (out);
}

void	free_strv(char **v)
{
	int	i;

	i = 0;
	if (!v)
		return ;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
}
