#include "minishell.h"

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
	check_heredoc(cmd);
	if (cmd->next == 0 && check_builtin(cmd->name))
		single_builtin(cmd);
	else
		ft_fork(pipe_cnt, cmd);
	return ;
}