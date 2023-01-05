/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:10:13 by jiyun             #+#    #+#             */
/*   Updated: 2022/03/29 16:47:25 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	free_all(char **ret)
{
	size_t	i;

	i = 0;
	while (ret[i] != 0)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
}

static size_t	put_str(char **ret, char const *cur, size_t size, size_t i)
{
	size_t	j;

	ret[i] = malloc(sizeof(char) * (size + 1));
	if (ret[i] == 0)
	{
		free_all(ret);
		return (0);
	}
	j = 0;
	while (j < size)
	{
		ret[i][j] = cur[j];
		j++;
	}
	ret[i][j] = '\0';
	return (1);
}

static size_t	cnt_strs(char const *str, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*str != '\0')
	{
		if (*str != c)
		{
			cnt++;
			while (*str != '\0' && *str != c)
				str++;
			str--;
		}
		str++;
	}
	return (cnt);
}

static char	**malloc_ret(char const *s, char c, size_t *size)
{
	char	**ret;

	if (!s)
		return (0);
	*size = cnt_strs(s, c);
	ret = malloc(sizeof(char *) * (*size + 1));
	if (ret == 0)
		return (0);
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	size;
	size_t	cnt;	
	size_t	i;

	ret = malloc_ret(s, c, &size);
	if (ret == 0)
		return (0);
	cnt = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			i = 0;
			while (*(s + i) != '\0' && *(s + i) != c)
				i++;
			if (put_str(ret, s, i, cnt++) == 0)
				return (0);
			s += i - 1;
		}
		s++;
	}
	ret[size] = 0;
	return (ret);
}
