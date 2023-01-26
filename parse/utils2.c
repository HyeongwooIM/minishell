//
// Created by jiyun on 2023/01/17.
//

#include "minishell.h"

void	free_token_lst(t_token *lst)
{
	t_token *tmp;

	if (!lst)
		return ;
//	while (lst)
//	{
//		tmp = lst;
//		lst = lst->next;
//		free(tmp);
//	}
	while (lst)
	{
		tmp = lst->next;
		free(lst->word);
		free(lst);
		lst = tmp;
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

char *ft_charjoin(char *str, char c)
{
    char *ret;
    int i;

    if (!str)
    {
        ret = malloc(sizeof(char) * 2);
        if (!ret)
            ft_error_exit("malloc error\n", 1);
        ret[0] = c;
        ret[1] = '\0';
        return (ret);
    }
    ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
    if (!ret)
        ft_error_exit("malloc error\n", 1);
    i = -1;
    while (str[++i])
        ret[i] = str[i];
    ret[i] = c;
    ret[++i] = '\0';
    return (ret);
}

char	*ft_strjoin_1to1(char *s1, char *s2)
{
    size_t	s1_len;
    size_t	s2_len;
    char	*new;

    if (!s1 && !s2)
        return (0);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));
    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);
    if (!s1_len && !s2_len)
        return (ft_strdup(""));
    new = malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (!new)
        return (0);
    ft_strlcpy(new, s1, s1_len + 1);
    ft_strlcpy(new + s1_len, s2, s2_len + 1);
    free(s1);
    return (new);
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