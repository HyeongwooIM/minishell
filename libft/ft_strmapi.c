/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:06:25 by jiyun             #+#    #+#             */
/*   Updated: 2022/03/28 17:41:30 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	i;

	if (!s || !f)
		return (0);
	ret = malloc(sizeof(char) * ft_strlen((char *)s) + 1);
	if (!ret)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		ret[i] = (*f)((unsigned int)i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
