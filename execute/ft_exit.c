#include "../minishell.h"

int check_content(char *str)
{
	if (*str && (*str == '-' || *str == '+'))
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void ft_exit(t_cmd *cmd)
{
	int	exit_num;
	unsigned int len;
	char **str;

	str = cmd->content;
	len = 0;
	if (!str)
		exit(0);
	if (str[1] != 0 && str[2] != 0)
		exit (1); //error 1
	if (check_content(*(cmd->content)) != 1)
		exit(1); //error
	exit_num = ft_atoi(*(cmd->content));
	exit(exit_num);
}