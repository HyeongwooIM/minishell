//
// Created by jiyun on 2023/01/22.
//
#include "minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{

	}
}

void	define_signal()
{
	signal(SIGINT, signal_handler);
}