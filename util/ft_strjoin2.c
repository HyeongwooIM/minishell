#include "minishell.h"

char **ft_strjoin2(char *str, char **arr)
{
	unsigned int	word_num;
	long			i;
	char			**res;

	word_num = 0;
	while (arr && arr[word_num])
		++word_num;
	res = (char **)malloc(sizeof(char *) * (word_num + 2));
	if (!res)
		ft_error_exit("malloc error", 1);
	res[word_num + 1] = 0;
	if (!res)
		return (0); //error
	res[0] = ft_strdup(str);
	if (!res[0])
		ft_error_exit("malloc error", 1);
	i = -1;
	while (++i < word_num)
	{
		res[i + 1] = ft_strdup(arr[i]);
		if (!res[i + 1])
			ft_error_exit("malloc error", 1);
	}
	return (res);
}