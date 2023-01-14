#include "../minishell.h"

void ft_pwd()
{
	char	get_cwd[PATH_MAX];

	if (!getcwd(get_cwd,sizeof(PATH_MAX)))
	{
		ft_putstr_fd("pwd error", 1);
		exit (1);
	}
	printf("%s\n",get_cwd);
}