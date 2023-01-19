/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:01:45 by jiyun             #+#    #+#             */
/*   Updated: 2022/03/23 20:25:45 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*tmp;

	len = ft_strlen(s1);
	tmp = malloc(sizeof(char) * (len + 1));
	if (tmp == 0)
		return (0);
	ft_strlcpy(tmp, s1, len + 1);
	return (tmp);
}
