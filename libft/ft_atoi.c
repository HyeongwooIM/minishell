/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:54:54 by him               #+#    #+#             */
/*   Updated: 2023/01/27 17:54:55 by him              ###   ########.fr       */
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
