/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:01:45 by jiyun             #+#    #+#             */
/*   Updated: 2023/01/22 18:24:43 by woohyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_error_exit(char *str, int error_no)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(error_no);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*tmp;

	len = ft_strlen(s1);
	tmp = malloc(sizeof(char) * (len + 1));
	if (tmp == 0)
		ft_error_exit("malloc error", 1);
	ft_strlcpy(tmp, s1, len + 1);
	return (tmp);
}
