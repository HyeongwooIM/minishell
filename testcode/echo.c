#include "../minishell.h"
#include <unistd.h>

#include "../minishell.h"

int	check_n(char *content)
{
	if (content[0] == '-' && content[1] == 'n')
		return (1);
	return (0);
}

void	ft_echo(t_cmd	*cmd)
{
	int	n;
	int	i;
	
	i = 0;
	n = 0;
	if (cmd->content[i]== '-' && cmd->content[i + 1] == 'n')
	{
		n = 1;
		i += 2;
	}
	while (cmd->content[i])
	{
		write(1, &cmd->content[i], 1);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
	return ;
}

int main()
{
	t_cmd cmd;

	cmd.name = "echo";
	cmd.content = "123 123 123 ";

	ft_echo(&cmd);
	return (0);
}