#include "../minishell.h"

char **ft_strjoin2(char *str, char **arr)
{
	long	word_num;
	long	word_len;
	long	i;
	char	**res;

	word_num = -1;
	while (arr[++word_num])
		;
	res = (char **)malloc(sizeof(char *) * word_num + 2);
	if (!res)
		return (1); //error
	res[word_num] = 0;
	i = -1;
	while (++i < word_num)

}