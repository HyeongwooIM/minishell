#include <stdio.h>
#include <unistd.h>
#include "../../minishell.h"

int main()
{
	char *a = "11";
	printf("=\"%s\"\n", a);
	return (0);
}

// int	check_n(char *content)
// {
// 	if (!content)
// 		return (0);
// 	if(*content == '-')
// 		content++;
// 	else
// 		return (0);
// 	while (*content == 'n')
// 		content++;
// 	if (*content == 0)
// 		return (1);
// 	return (0);
// }

// void	ft_echo(char **str)
// {
// 	int	n;

// 	n = check_n(*str);
// 	if (n)
// 		str++;
// 	while (*str)
// 	{
// 		ft_putstr_fd(*str, 1);
// 		str++;
// 		if(*str)
// 			write(1, " ", 1);
// 	}
// 	if (!n)
// 		write(1, "\n", 1);
// 	return ;
// }

// int main(int ac, char **av)
// {
// 	if (ac)
// 	{
// 		av++;
// 		// printf("%s", av[0]);
// 		ft_echo(av);
// 	}
// 	return (0);
// }

// int check_content(char *str)
// {
// 	if (*str && (*str == '-' || *str == '+'))
// 		str++;
// 	while (*str)
// 	{
// 		if (!ft_isdigit(*str))
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

// void ft_exit(char **str)
// {
// 	int	exit_num;
	// unsigned int len;
	// char **temp;

	// temp = str;
	// str++;;
	// len = -1;
	// while (*temp && ++len >= 0)
	// 	temp++;
	// printf("%d", len);
	// if (len > 1)
	// 	return ; //error 1
	// if (!check_content(*(str)))
	// 	exit(1); //error
// 	str++;
// 	exit_num = ft_atoi(*(str));
// 	printf("%d", exit_num);
// 	exit(exit_num);
// }

// int main(int ac, char **av)
// {
// 	if (ac)
// 	{
// 	ft_exit(av);
// 	}
// 	return (0);
// }


// int main ()
// {
// 	char *str[5] = {"1234444", "456", "789"};
// 	char **arr = str;
// 	int len = 0;
// 	while (*arr && len++ >= 0)
// 		arr++;
// 	printf("%d", len);
// 	return (0);
// }

// int check_content(char *str)
// {
// 	if (*str && (*str == '-' || *str == '+'))
// 		str++;
// 	while (*str)
// 	{
// 		str++;
// 	}
// 	return (1);
// }


// int main(int ac, char **av)
// {
// 	if (ac && av)
// 	{
// 		printf("%d", check_content(av[0]));
// 	}
// 	return (0);
// }