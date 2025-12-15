/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:59:14 by qabdel-r          #+#    #+#             */
/*   Updated: 2025/12/14 14:27:14 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    close_safe(int *fd)
{
    if (fd == NULL)            // if someone passed NULL pointer, do nothing
        return;
    if (*fd >= 0)              // only close valid fds (0,1,2,...)
    {
        close(*fd);            // close the fd
        *fd = -1;              // VERY important: mark it as closed
    }
}
void    cleanup(int *infile, int *outfile, int pipefd[2])
{
    close_safe(&pipefd[0]);
    close_safe(&pipefd[1]);
    close_safe(infile);
    close_safe(outfile);
}
size_t ft_strlen(const char *s)
{
    size_t i;
    i =0;
    while(s&& s[i])
        i++;
    return i;
}
int  ft_strncmp(const char * a,const char *b,size_t n)
{
    size_t  i;
    i =0;
    while (i <n && a[i]&& b[i] && a[i] == b[i])
        i++;
    if (i == n)
        return 0;
    return((unsigned char)a[i] - (unsigned char)b[i]);
}
char    *ft_strchr(const char *s, int c)
{
    size_t  i;
    char    *p;

    i = 0;
    if (!s)
        return NULL;
    while (s[i])
    {
        if ((unsigned char)s[i] == (unsigned char)c)
        {
            p = (char *)s;
            p = p + i;
            return p;
        }
        i++;
    }
    if ((unsigned char)c == '\0')
    {
        p = (char *)s;
        p = p + i;
        return p;
    }
    return NULL;
}

void    free_strv(char **v)
{
    int     i;
    i =0;
    if(!v)
        return;
    while (v[i])
    {
        free(v[i]);
        i++;
    }
    free(v);
}
 int  is_space(char c)
{
    if (c == ' ')
        return 1;
    if (c == '\t')
        return 1;
    return 0;
}
char *substr_dup(const char *s,int start,int end)
{
    int len;
    char *out;
    int i;

    len = end -start;
    out = (char *) malloc ((size_t) len +1);
    i = 0;

    if (!out)
        return NULL;

    while (start +1 < end)
    {
        out[i] =s[start +i];
        i++;
    }
    out[i] = '\0';
    return out;
}
int  count_words_ws(const char *s)
{
    int i;
    i = 0;
    int count ;
    count  = 0;

    while (s && s[i])
    {
        while (s[i] && is_space(s[i]))
            i++;
        if (s[i])
            count++;
        while (s[i] && !is_space(s[i]))
            i++;
    }
    return count;
}
char	**split_ws(const char *s)
{
	char	**out;
	int		words;

	if (!s)
		return (NULL);
	words = count_words_ws(s);
	out = (char **)malloc(sizeof(char *) * (words + 1));
	if (!out)
		return (NULL);
	if (fill_split(out, s, words) == -1)
		return (NULL);
	return (out);
}
int	fill_split(char **out, const char *s, int words)
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
	out[i++] = '/';
	j = 0;
	while (j < b)
		out[i++] = cmd[j++];
	out[i] = '\0';
	return (out);
}
yy
