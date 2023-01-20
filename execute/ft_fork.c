#include "../minishell.h"

void ft_fork(int pipe_cnt, t_cmd *cmd)
{
	int **pipes;
	int i;
	pid_t pid;

	i = -1;
	pipes = ft_calloc(pipe_cnt + 1, sizeof(int *));
	while (++i < pipe_cnt)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (pipe(pipes[i]))
			exit (1);
	}
	i = -1;
	while (++i <= pipe_cnt)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != pipe_cnt)
				dup2(pipes[i][1],STDOUT_FILENO);
			if (i != 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			pipe_close(pipes, i, pipe_cnt);
			ft_rdir(cmd->rdir);
			if (check_builtin(cmd->name))
				single_builtin(cmd, g_info.env_lst);
			else
				ft_exe(cmd, g_info.env_lst);
			exit(0);
		}
		cmd = cmd->next;
	}
	i = -1;
	while (++i <= pipe_cnt)
		wait(1);
	return ;
}