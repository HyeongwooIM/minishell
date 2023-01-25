//
// Created by jiyun on 2023/01/22.
//

#include "minishell.h"

void	heredoc_sigint_handler(int signo)
{
	ft_putendl_fd("", STDOUT_FILENO);
	exit(1);
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_info.last_exit_num = 1;
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_terminal()
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	define_signal()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}