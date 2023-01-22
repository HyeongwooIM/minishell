#include "minishell.h"

void ft_fork(int pipe_cnt, t_cmd *cmd)
{
	int pipes[2][2];
	int i;
	pid_t pid;
	int status;


	i = -1;
	while (++i <= pipe_cnt)
	{
		if (pipe(pipes[0]) == -1)
			ft_error_exit("pipe error", 1);
		pid = fork();
		if (pid == -1)
			ft_error_exit("fork error", 1);
		if (pid == 0)
		{
			close(pipes[0][0]);
			if (pipe_cnt && i != pipe_cnt)
            {
				dup2(pipes[0][1],STDOUT_FILENO);
                close(pipes[0][1]);
            }
			if (i != 0)
            {
				dup2(pipes[1][0], STDIN_FILENO);
                close(pipes[1][0]);
            }
            if (cmd->rdir)
				ft_rdir(cmd->rdir);
			if (check_builtin(cmd->name))
                is_builtin(cmd);
			else
				ft_exe(cmd, g_info.env_lst);
			exit(0);
		}
		close(pipes[0][1]);
		if (i > 0)
			close(pipes[1][0]);
        pipes[1][0] = pipes[0][0];
        if (i == pipe_cnt)
            close((pipes[0][0]));
		cmd = cmd->next;
	}
	i = -1;
	while (++i <= pipe_cnt)
		wait(&status);
	status = status >> 8;
	g_info.last_exit_num = status;
	return ;
}