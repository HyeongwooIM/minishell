#include "minishell.h"

void ft_error_return(char *str, int error_no)
{
	write(2, str, ft_strlen(str));
}

void ft_error_exit(char *str, int error_no)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(error_no);
}

void	ft_command_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_info.last_exit_num = 127;
	exit(127);
}