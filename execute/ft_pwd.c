#include "minishell.h"

void ft_pwd()
{
	char	get_cwd[1024];

	if (!getcwd(get_cwd,4096))
	{
		ft_putstr_fd("pwd error", 1);
		exit (1);
	}
	printf("%s\n",get_cwd);
}