/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:11:04 by him               #+#    #+#             */
/*   Updated: 2023/01/27 16:48:12 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_new_env(char *key)
{
	t_env	*node;

	node = malloc(sizeof(t_env) * 1);
	if (!node)
		ft_error_exit("malloc error", 1);
	node->key = ft_strdup(key);
	node->value = 0;
	node->next = NULL;
	return (node);
}

t_env	*find_env_add(char *key)
{
	t_env	*temp;

	temp = g_info.env_lst;
	if (!temp)
	{
		temp = create_new_env(key);
		g_info.env_lst = temp;
		return (temp);
	}
	while (ft_strcmp(temp->key, key) && temp->next != 0)
		temp = temp->next;
	if (ft_strcmp(temp->key, key) && temp->next == 0)
	{
		temp->next = create_new_env(key);
		temp = temp->next;
	}
	return (temp);
}
