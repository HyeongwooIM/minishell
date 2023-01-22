#include "minishell.h"

t_env *find_env(char *key)
{
	t_env *temp;

	temp = g_info.env_lst;
	while (temp && ft_strcmp(temp->key, key))
		temp = temp->next;
	if (!temp)
		return (0);
	return (temp);
}