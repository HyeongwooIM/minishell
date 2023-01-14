#include "../minishell.h"

void epxort_null_print()
{
	t_env *env;

	env = g_info->env_list;
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"\n", env->value); //"" test gogo
		env = env->next;
	}
}

void ft_export(t_cmd *cmd)
{
	t_env	*temp;
	char	**env_arr;
	char	**key_value;

	key_value = cmd->content;
	if (!*cmd->content)
	{
		export_null_print();
		return ;
	}
	temp = find_env_add(*key_value);
	key_value++;
	if (!key_value)
		return ;
	
	env_arr = ft_split(cmd->content, '=');
	if (!env_arr)
		exit(1); //error
	new_env->key = ft_strdup(env_arr[0]);
	//널가드??...
	new_env->value = ft_strdup(env_arr[1]);
	return ;
}