/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:33:46 by jiyun             #+#    #+#             */
/*   Updated: 2022/03/29 17:41:03 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*first;
	char	*end;
	char	*part;
	int		len;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	first = (char *)s1;
	while (*first && ft_strchr(set, *first))
		first++;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (first <= end && ft_strchr(set, *end))
		end--;
	len = end - first + 1;
	part = malloc(sizeof(char) * (len + 1));
	if (!part)
		return (0);
	ft_strlcpy(part, first, len + 1);
	return (part);
}
