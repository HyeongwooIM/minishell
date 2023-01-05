/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:50:48 by jiyun             #+#    #+#             */
/*   Updated: 2022/04/01 15:41:51 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!s1_len && !s2_len)
		return (ft_strdup(""));
	new = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new)
		return (0);
	ft_strlcpy(new, s1, s1_len + 1);
	ft_strlcpy(new + s1_len, s2, s2_len + 1);
	return (new);
}
