/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:06:06 by him               #+#    #+#             */
/*   Updated: 2023/01/27 16:33:24 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env) * 1);
	if (!node)
		ft_error_exit("malloc error", 1);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	save_envs(char *envp[])
{
	t_env	*cur;
	t_env	*head;
	t_env	*tmp;
	char	**path;
	int		i;

	path = ft_split(envp[0], '=');
	cur = new_env(path[0], path[1]);
	head = cur;
	free_arr2(path);
	i = 1;
	while (envp[i] != NULL)
	{
		path = ft_split(envp[i], '=');
		tmp = new_env(path[0], path[1]);
		cur->next = tmp;
		cur = cur-> next;
		i++;
		free_arr2(path);
	}
	g_info.env_lst = head;
}

char	*join_three(char *start, char *end, char *middle)
{
	char	*join_two;
	char	*ret;

	join_two = ft_strjoin(start, middle);
	ret = ft_strjoin(join_two, end);
	free(join_two);
	return (ret);
}

size_t	get_size(t_env *envs)
{
	size_t	size;

	size = 0;
	while (envs != NULL)
	{
		envs = envs->next;
		size++;
	}
	return (size);
}

char	**lst_to_arr(t_env *envs)
{
	char		**arr;
	size_t		size;
	size_t		i;

	size = get_size(envs);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		ft_error_exit("malloc error", 1);
	arr[size] = 0;
	i = 0;
	while (i < size && envs != NULL)
	{
		arr[i] = join_three(envs->key, envs->value, "=");
		envs = envs->next;
		i++;
	}

	return (arr);
}
