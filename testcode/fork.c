#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int **pipes;
    pid_t pid;
	int i;
	int pipe_cnt;

	pipe_cnt = 3;
	pipes = malloc(sizeof(int *) * (pipe_cnt + 1));
	pipes[pipe_cnt] = 0;
	i = -1;
	while (i++ < pipe_cnt)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
	}
	i = -1;
	while (++i < pipe_cnt + 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != pipe_cnt)
				dup2(pipes[i][1],STDOUT_FILENO);
			if (i != 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
		}
	}

    return 0;
}
