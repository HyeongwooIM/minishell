#include "minishell.h"

t_info g_info;

void	free_cmds(t_cmd *cmds)
{
	t_cmd *tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free(cmds->name);
		free_arr2(cmds->content);
		free_rdir_lst(cmds->rdir);
		free(cmds);
		cmds = tmp;
	}
}

void	handle_terminal()
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmds;

	if (argc != 1)
	{
		ft_putendl_fd("too many arguments", STDERR_FILENO);
		exit(FAIL);
	}
	save_envs(envp);
	while(1)
	{
		cmds = NULL;
		handle_terminal();
		define_signal();
		parse(&cmds);
		execute(cmds);
		free_cmds(cmds);
	}
}
