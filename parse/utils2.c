//
// Created by jiyun on 2023/01/17.
//

#include "minishell.h"
#include "parse.h"

void	free_token_lst(t_token *lst)
{
	t_token *tmp;

	if (!lst)
		return ;
	if (!lst->next)
	{
		free(lst);
		lst = NULL;
	}
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void free_rdir_lst(t_rdir *lst)
{
	t_rdir *tmp;

	if (!lst)
		return ;
	if (!lst->next)
	{
		free(lst);
		lst = NULL;
	}
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	free_arr2(char **ret)
{
    size_t	i;

    i = 0;
	if (!ret)
		return ;
    while (ret[i] != 0)
    {
        free(ret[i]);
        i++;
    }
    free(ret);
}

char	**ft_strjoin_1to2(char **dest, char *src)
{
	unsigned int	word_num;
	long			i;
	char	**res;

    word_num = 0;
	if (!src && !dest)
		return (0);
	if (!src)
		return (dest);
	if (!dest)
		res = malloc(sizeof(char *) * 2);
	else
	{
		while (dest[word_num])
			++word_num;
		res = malloc(sizeof(char *) * (word_num + 2));
	}
	if (!res)
		ft_error_exit("malloc error", 1);
	i = -1;
	while (++i < word_num)
		res[i] = ft_strdup(dest[i]);
	res[word_num] = ft_strdup(src);
	res[word_num + 1] = 0;
	if (dest)
		free_arr2(dest);
	return (res);
}