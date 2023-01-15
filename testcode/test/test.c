#include <stdio.h>
#include <unistd.h>
#include "../../minishell.h"

char **find_key_value(char *key_value)
{
	char **res;
	unsigned int len;

	res = malloc(sizeof(char *) * 3);
	if (!ft_strchr(key_value, '='))
	{
		res = malloc(sizeof(char *) * 2);
		res[0] = ft_strdup(key_value);
		res[1] = 0;
		return (res);
	}
	res = malloc(sizeof(char *) * 3);
	len = ft_strchr(key_value, '=') - key_value;
	res[0] = malloc(sizeof(char) * len + 1);
	ft_strlcpy(res[0], key_value, len + 1);
	res[1] = ft_strdup(key_value + len + 1);
	res[2] = 0;
	return (res);
}

int main()
{
	char **str;

	str = find_key_value("str123=123123123=123=123=");
	if (str)
		printf("key = %s\nvalue = %s", str[0], str[1]);
	else
		printf("key = %s\n", str[0]);
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