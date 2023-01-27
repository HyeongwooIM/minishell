/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:06:02 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/27 14:06:03 by woohyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_lst(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst->word);
		free(lst);
		lst = tmp;
	}
}

void	free_rdir_lst(t_rdir *lst)
{
	t_rdir	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst->with);
		free(lst);
		lst = tmp;
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

char	**ft_strjoin_1to2(char **dest, char *src, int size)
{
	long	i;
	char	**res;

	if (!src && !dest)
		return (0);
	if (!src)
		return (dest);
	if (!dest)
		res = malloc(sizeof(char *) * 2);
	else
	{
		while (dest[size])
			++size;
		res = malloc(sizeof(char *) * (size + 2));
	}
	if (!res)
		ft_error_exit("malloc error", 1);
	i = -1;
	while (++i < size)
		res[i] = ft_strdup(dest[i]);
	res[size] = ft_strdup(src);
	res[size + 1] = 0;
	if (dest)
		free_arr2(dest);
	return (res);
}
