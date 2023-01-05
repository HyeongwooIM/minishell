/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:25:46 by jiyun             #+#    #+#             */
/*   Updated: 2022/04/01 17:14:18 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cast_b;
	unsigned char	cast_c;

	cast_b = (unsigned char *)b;
	cast_c = (unsigned char)c;
	while (len--)
	{
		*cast_b = cast_c;
		cast_b++;
	}
	return (b);
}
