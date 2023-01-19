#include "../minishell.h"

int check_pipe(t_cmd *cmd)
{
	unsigned int num;

	num = 0;
	while (cmd && cmd->next)
	{
		cmd = cmd->next;
		num++;
	}
	return (num);
}

int **set_pipe(int pipe_cnt)
{
	int i;
	int **pipes;

	i = 0;
	if (pipe_cnt >= 1)
		pipes = malloc(sizeof(int *) * (pipe_cnt + 1));
	if (!pipes)
		exit(1);
	pipes[pipe_cnt] = 0;
	while (pipes[i])
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			exit(1);
		if (!pipe(pipes[i]))
			exit(1); // pipe_error
		i++;
	}
	
}

void ft_pipe()
{

}