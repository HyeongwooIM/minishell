/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:33:07 by jiyun             #+#    #+#             */
/*   Updated: 2022/04/01 15:32:58 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*needle))
		return ((char *)haystack);
	j = 0;
	while (j < len && *haystack != '\0')
	{
		i = 0;
		while ((*(haystack + i) == *(needle + i)) && (*(needle + i) != '\0') \
				&& (j + i < len))
			i++;
		if (i == ft_strlen(needle))
			return ((char *)haystack);
		haystack++;
		j++;
	}
	return (0);
}
