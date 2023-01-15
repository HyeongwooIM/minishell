#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

int main()
{

	int fd;
	char *a ="aaa";
	char *str;
	int len;

	fd = open(a, O_CREAT | O_WRONLY, S_IRUSR);
	while (fd > 0)
	{
		str = readline("> ");
		len = strlen(str);
		if (strcmp(str, "a") == 0)
			break;
		else if (!str)
			break;
		write(fd, str, len);
		free(str);
	}
	return (0);
}