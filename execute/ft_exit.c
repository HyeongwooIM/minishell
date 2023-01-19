#include "../minishell.h"

int check_content(char *str)
{
	if (*str && (*str == '-' || *str == '+'))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
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
	while (*str && len++ >= 0)
		str++;
	if (len > 1)
		return ; //error 1
	if (!check_content(*(cmd->content)));
		exit(1); //error
	exit_num = ft_atoi(*(cmd->content));
	exit(exit_num);
}