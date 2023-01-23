/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:57:57 by jiyun             #+#    #+#             */
/*   Updated: 2023/01/22 22:09:01 by woohyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	if (!dest || !src)
		return (0);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (src && src[i] != '\0' && i + 1 < dstsize)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
