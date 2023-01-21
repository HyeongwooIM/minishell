#include "../minishell.h"

// void	execute(t_cmd	*cmd, t_env *env)
// {
// 	int	pipe_cnt;

// 	if (!cmd)
// 		return ;
// 	pipe_cnt = check_pipe(cmd);
// 	check_heredoc(cmd);
// 	if (cmd->next == 0 && check_builtin(cmd->name))
// 		single_builtin(cmd, env);
// 	else
// 		ft_exe(cmd);
// 	if (pipe_cnt > 0)
// 	{
// 		while (pipe_cnt-- >= 0)
// 		{
// 		int pid;
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			redir(cmd);
// 			pipe();
// 			child_pro();
// 		}
// 		cmd = cmd->next;
// 		}
// 	}
// 	return ;
// }

int pipe_count(t_cmd *cmd)
{
	int count;

	count = -1;
	while (cmd)
	{
		cmd = cmd->next;
		count++;
	}
	return (count);
}

void execute(t_cmd *cmd)
{
	int	pipe_cnt;
	t_env *env;

	env = g_info.env_lst;
	pipe_cnt = pipe_count(cmd);
	check_heredoc(cmd); // create_heredoc ok
	if (cmd->next == 0 && check_builtin(cmd->name))
		single_builtin(cmd, env);
	else
		ft_fork(pipe_cnt, cmd);
	return ;
}