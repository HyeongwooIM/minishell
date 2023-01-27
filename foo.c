#include <stdio.h>

int main(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		printf("[%d], \"%s\"\n", i, argv[i]);
		i++;
	}
}
