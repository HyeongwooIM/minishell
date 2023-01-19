#include "../minishell.h"
#include <readline/readline.h>

int main()
{
    char *str;

    while (1)
    {
	str = readline("> ");
    printf("str : %s \n", str);
    };

	return (0);
}