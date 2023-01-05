/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:21:59 by jiyun             #+#    #+#             */
/*   Updated: 2022/03/27 17:13:10 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	put_num(char *ret, long n, int size)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		ret[0] = '-';
		n *= -1;
		i++;
	}
	while (size > i)
	{
		ret[size - 1] = n % 10 + '0';
		n /= 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	int		size;
	char	*ret;

	size = num_len(n);
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (0);
	put_num(ret, (long)n, size);
	ret[size] = '\0';
	return (ret);
}
