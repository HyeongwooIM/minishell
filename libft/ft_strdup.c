/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:55:00 by him               #+#    #+#             */
/*   Updated: 2023/01/27 17:55:01 by him              ###   ########.fr       */
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
