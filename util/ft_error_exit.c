#include "minishell.h"

void ft_error_return(char *str, int error_no)
{
	write(2, str, ft_strlen(str));
}

void ft_error_exit(char *str, int error_no)
{
	write(2, str, ft_strlen(str));
	exit(error_no);
}