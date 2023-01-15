#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		s++;
		len++;
	}
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (fd < 0 || !s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

int	check_n(char *content)
{
	if(*content == '-')
		content++;
	else
		return (0);
	while (*content == 'n')
		content++;
	if (*content == 0)
		return (1);
	return (0);
}

void	ft_echo(t_cmd	*cmd)
{
	int	n;
	char **str;
	
	str = cmd->content;
	n = check_n(*str);
	if (n)
		str++;
	while (*str)
	{
		ft_putstr_fd(*str, 1);
		str++;
		if( *str)
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	return ;
}

int main(int argc, char **argv)
{
	t_cmd cmd;
	if (argc && argv[0])
		;
	char *str[10] = {"-n", "123", "132"};

	// printf("%c", str[0][1]);
	cmd.content = str;

	// printf("%s", envp[0]);
	ft_echo(&cmd);
	return (0);
}