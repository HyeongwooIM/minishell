#include "../minishell.h"

char **find_key_value(char *key_value)
{
	char **res;
	unsigned int len;

	if (!ft_strchr(key_value, '='))
	{
		res = malloc(sizeof(char *) * 2);
		res[0] = ft_strdup(key_value);
		res[1] = 0;
		return (res);
	}
	res = malloc(sizeof(char *) * 3);
	len = ft_strchr(key_value, '=') - key_value;
	res[0] = malloc(sizeof(char) * len + 1);
	ft_strlcpy(res[0], key_value, len + 1);
	res[1] = ft_strdup(key_value + len + 1);
	res[2] = 0;
	return (res);
}

void epxort_null_print()
{
	t_env *env;

	env = g_info->env_list;
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"\n", env->value);
		env = env->next;
	}
}

void ft_export(t_cmd *cmd)
{
	t_env	*temp;
	char	**env_arr;
	char	*key_value;

	key_value = *cmd->content;
	if (!*key_value)
	{
		export_null_print();
		return ;
	}
	env_arr = find_key_value(key_value);
	temp = find_env_add(env_arr[0]);
	if (env_arr[1])
		temp->value = ft_strdup(env_arr[1]); //env_arr free gogo
	while (*env_arr)
	{
		free(*env_arr);
		*env_arr++;
	}
	free(*env_arr);
	free(env_arr);
	// key_value++;
	// if (!key_value)
	// 	return ;
	// env_arr = ft_strchr(*key_value, '=');
	// if (!env_arr)
	// 	exit(1); //error
	// new_env->key = ft_strdup(env_arr[0]);
	// //널가드??...
	// new_env->value = ft_strdup(env_arr[1]);
	return ;
}