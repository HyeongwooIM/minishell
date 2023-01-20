/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:18:37 by jiyun             #+#    #+#             */
/*   Updated: 2023/01/16 19:11:01 by woohyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\t' || c == '\v' || \
			c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		cnt;
	int		sign;
	long	ret;

	cnt = 0;
	sign = 1;
	ret = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
	{
		ret = ret * 10 + (*str - '0');
		cnt++;
		str++;
		if ((cnt > 19 && sign == -1) || (ret < 0 && sign == -1))
			return ((int)(-9223372036854775807 - 1));
		else if ((cnt > 19 && sign == 1) || (ret < 0 && sign == 1))
			return ((int)9223372036854775807);
	}
	return ((int)ret * sign);
}
