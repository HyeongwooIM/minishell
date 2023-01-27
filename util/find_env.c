/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:49:00 by him               #+#    #+#             */
/*   Updated: 2023/01/26 21:53:12 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(char *key)
{
	t_env	*temp;

	temp = g_info.env_lst;
	while (temp && ft_strcmp(temp->key, key))
		temp = temp->next;
	if (!temp)
		return (0);
	return (temp);
}
