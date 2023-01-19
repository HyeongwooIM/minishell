#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>

int main()
{
	char *str;
	int len = 0;
	int	fd[2];
	char arr[6];

	pipe(fd);
	while (1)
	{
		str = readline(">");
		while (*str)
		{
			write(fd[1], str, 1);
			str++;
			len++;
		}
		write(fd[1], "\n", 1);
		len++;
		if (len > 30)
			break ;
	}
	close(fd[1]);
	read(fd[0], arr, 5);
	printf("%s", arr);
	return (0);
}