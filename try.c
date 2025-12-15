
// #include <string.h>
// #include <unistd.h>
// #include <unistd.h>

// /* ---------- small utils ---------- */

// static int	ft_strlen(const char *s)
// {
// 	int i = 0;
// 	while (s && s[i])
// 		i++;
// 	return i;
// }

// static int	ft_startswith(const char *s, const char *prefix)
// {
// 	int i = 0;
// 	while (prefix[i])
// 	{
// 		if (s[i] != prefix[i])
// 			return 0;
// 		i++;
// 	}
// 	return 1;
// }

// /* ---------- get PATH value from envp ---------- */
// /* returns pointer to the value after "PATH=" or NULL if not found */
// static char	*get_path_value(char **envp)
// {
// 	int i = 0;

// 	while (envp && envp[i])
// 	{
// 		if (ft_startswith(envp[i], "PATH="))
// 			return envp[i] + 5; /* skip "PATH=" */
// 		i++;
// 	}
// 	return 0;
// }

// /* ---------- print PATH directories line by line ---------- */
// static void	print_path_dirs(char *path)
// {
// 	int start = 0;
// 	int i = 0;

// 	if (!path)
// 		return ;

// 	while (1)
// 	{
// 		if (path[i] == ':' || path[i] == '\0')
// 		{
// 			int len = i - start;

// 			/* إذا كان في جزء فاضي (مثل ::) هذا يعني current dir */
// 			if (len == 0)
// 				write(1, ".\n", 2);
// 			else
// 			{
// 				write(1, path + start, len);
// 				write(1, "\n", 1);
// 			}

// 			if (path[i] == '\0')
// 				break;

// 			start = i + 1;
// 		}
// 		i++;
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char *path;

// 	(void)argc;
// 	(void)argv;

// 	path = get_path_value(envp);
// 	if (!path)
// 	{
// 		write(2, "PATH not found\n", 15);
// 		return 1;
// 	}

// 	print_path_dirs(path);
// 	return 0;
// }

// #include <unistd.h>
// #include <sys/types.h>
// #include <stdio.h>

// int main(void)
// {
//     pid_t pid;

//     pid = fork();                 // يصنع عملية ابن

//     if (pid == -1)                // فشل
//         return 1;

//     if (pid == 0)                 // نحن داخل الابن
//     {
//         printf("Child:  pid=%d, parent=%d\n", getpid(), getppid());
//     }
//     else                          // نحن داخل الأب
//     {
//         printf("Parent: pid=%d, child=%d\n", getpid(), pid);
//     }
//     return 0;
// }

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("out.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    dup2(fd, 1);        // stdout (1) صار يكتب على out.txt
    close(fd);          // ما عاد نحتاج fd الأصلي

    printf("hello\n");  // رح تنكتب داخل out.txt مش على الشاشة
    return 0;
}
