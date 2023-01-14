#include "../minishell.h"

t_env *find_env_add(char *key)
{
	t_env *temp;

	temp = g_info->env_list;
	if (!temp)
	{
		temp = new_env(key, 0);
		g_info->env_list = temp;
	}
	while (ft_strcmp(temp->key, key) && temp->next)
		temp = temp->next;
	if (ft_strcmp(temp->key, key) && !temp->next)
	{
		temp->next = new_env(key, 0);
		temp = temp->next;
	}
	if (!temp)
		exit(1);
	return (temp);
}