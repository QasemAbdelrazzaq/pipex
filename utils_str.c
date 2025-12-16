#include "pipex.h"

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	return (0);
}

int	is_all_space(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (!is_space(s[i]))
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	while (i < n && a[i] && b[i] && a[i] == b[i])
		i++;
	diff = 0;
	if (i == n)
		return (diff);
	diff = (unsigned char)a[i] - (unsigned char)b[i];
	return (diff);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			p = (char *)s;
			p = p + i;
			return (p);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
	{
		p = (char *)s;
		p = p + i;
		return (p);
	}
	return (NULL);
}

